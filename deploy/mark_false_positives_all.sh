#!/usr/bin/env bash
set -euxo pipefail

SONAR_HOST="https://sonarcloud.io"
PROJECT_KEY="Sidelobe_Sonarcloud-CppFalsePositives"
SONAR_TOKEN="${SONAR_TOKEN:?SONAR_TOKEN not set}"

PAGE_SIZE=500
page=1
total_marked=0

echo "Starting SonarQube C++ FALSE_POSITIVE cleanup for $PROJECT_KEY"

while :; do
  response=$(curl -s --request GET --header "Authorization: Bearer $SONAR_TOKEN" \
    --url "$SONAR_HOST/api/issues/search?componentKeys=$PROJECT_KEY&statuses=OPEN,CONFIRMED,REOPENED&ps=$PAGE_SIZE&p=$page")
  
  issue_count=$(jq '.issues | length' <<< "$response")
  
  [ "$issue_count" -eq 0 ] && break
  
  echo "$issue_count Issues are OPEN"

  while IFS= read -r issue; do
    key=$(jq -r '.key' <<< "$issue")
    rule=$(jq -r '.rule' <<< "$issue")
    path=$(jq -r '.component' <<< "$issue")
  
    if [[ "$rule" =~ ^(cpp|cxx): ]] && [[ "$path" =~ \.h$ ]]; then
      echo "→ C++ rule being applied to C code: $key ($rule) $path"
  
      curl -s -u "$SONAR_TOKEN:" --request POST \
        "$SONAR_HOST/api/issues/do_transition" \
        -d "issue=$key" \
        -d "transition=falsepositive" \
        >/dev/null
  
      total_marked=$((total_marked + 1))
    fi
  done < <(jq -c '.issues[]' <<< "$response")

  page=$((page + 1))
done

echo "Done. Marked $total_marked issues as FALSE_POSITIVE."
