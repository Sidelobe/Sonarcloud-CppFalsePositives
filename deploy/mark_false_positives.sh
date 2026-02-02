#!/usr/bin/env bash

# A bash script to disable all Sonarqube issues that were created due to C++ rules
# but were raised in C (header) files. The issues are set to 'falsepositive'
# This is applied either to '-all', or only to the issues that were raised in '-pr <number>'
# -> https://github.com/Sidelobe/Sonarcloud-CppFalsePositives

set -euo pipefail


SONAR_HOST="https://sonarcloud.io"
PROJECT_KEY="Sidelobe_Sonarcloud-CppFalsePositives"
SONAR_TOKEN="${SONAR_TOKEN:?SONAR_TOKEN not set}"

PAGE_SIZE=500
page=1
total_marked=0

echo "Starting SonarQube C++ FALSE_POSITIVE cleanup for $PROJECT_KEY"

### ------------ HANDLE INPUT PARAMETERS -------------
ALL=false
PR_NUMBER=""
DRY_RUN=false
SEEN_OPTION=false

while [[ $# -gt 0 ]]; do
    case "$1" in
        --all)
            if $SEEN_OPTION; then
                echo "Error: --all cannot be combined with other primary options"
                exit 1
            fi
            ALL=true
            SEEN_OPTION=true
            shift
            ;;

        --pr)
            if $SEEN_OPTION; then
                echo "Error: --pr cannot be combined with other primary options"
                exit 1
            fi

            if [[ -z "$2" ]]; then
                echo "Error: --pr requires a number"
                exit 1
            fi

            if ! [[ "$2" =~ ^[0-9]+$ ]]; then
                echo "Error: --pr expects a numeric value, got '$2'"
                exit 1
            fi

            PR_NUMBER="$2"
            SEEN_OPTION=true
            shift 2
            ;;

        --dry-run)
            DRY_RUN=true
            shift
            ;;

        *)
            echo "Unknown option: $1"
            exit 1
            ;;
    esac
done

# Enforce exactly one primary option
if ! $SEEN_OPTION; then
    echo "Error: you must specify either --all or --pr <number>"
    exit 1
fi

### ------------ GO THROUGH ISSUES AND SET TO FALSE_POSITIVE -------------
while :; do
  if $ALL; then
    response=$(curl -s --request GET --header "Authorization: Bearer $SONAR_TOKEN" \
      --url "$SONAR_HOST/api/issues/search?componentKeys=$PROJECT_KEY&statuses=OPEN,CONFIRMED,REOPENED&ps=$PAGE_SIZE&p=$page")
  else
    response=$(curl -s --request GET --header "Authorization: Bearer $SONAR_TOKEN" \
      --url "$SONAR_HOST/api/issues/search?componentKeys=$PROJECT_KEY&pullRequest=$PR_NUMBER&inNewCodePeriod=true&ps=$PAGE_SIZE&p=$page")
  fi
  issue_count=$(jq '.issues | length' <<< "$response")
  
  [ "$issue_count" -eq 0 ] && break
  
  echo "$issue_count Issues are OPEN"

  while IFS= read -r issue; do
    key=$(jq -r '.key' <<< "$issue")
    rule=$(jq -r '.rule' <<< "$issue")
    path=$(jq -r '.component' <<< "$issue")
  
    if [[ "$rule" =~ ^(cpp|cxx): ]] && [[ "$path" =~ \.h$ ]]; then
      echo "→ C++ rule being applied to C code: $key ($rule) $path"
  
      if !$DRY_RUN; then
        curl -s -u "$SONAR_TOKEN:" --request POST \
          "$SONAR_HOST/api/issues/do_transition" \
          -d "issue=$key" \
          -d "transition=falsepositive" \
          >/dev/null
      fi
  
      total_marked=$((total_marked + 1))
    fi
  done < <(jq -c '.issues[]' <<< "$response")

  page=$((page + 1))
done

if $DRY_RUN; then
  echo "Done. (DRY RUN) Marked $total_marked issues as FALSE_POSITIVE (DRY RUN)."
else
  echo "Done. Marked $total_marked issues as FALSE_POSITIVE."
fi
