
# Mixed C/C++ Code: Mark False-Positives (C++ rules in C code)

![](https://img.shields.io/github/license/Sidelobe/Sonarcloud-CppFalsePositives)

# Sonar Scanner Issues
Take a look at these [Issues on Main branch](https://sonarcloud.io/project/issues?issueStatuses=OPEN%2CCONFIRMED&id=Sidelobe_Sonarcloud-CppFalsePositives). They are all reported for `example1.h`, which is clearly a C file! They only show up because that header file is included in a C++ file (compilation unit).

### *--> Why are these issues not filtered out?*

[![Quality gate](https://sonarcloud.io/api/project_badges/quality_gate?project=Sidelobe_Sonarcloud-CppFalsePositives)](https://sonarcloud.io/summary/new_code?id=Sidelobe_Sonarcloud-CppFalsePositives)

## Examples of C++ Rules that are erroneously applied to C Code

- _The global namespace should only contain "main", namespace declarations, and "extern" C declarations cpp:S997_

- _"nullptr" should be used to denote the null pointer cpp:S4962_

- Declare the variable "k" inside the loop.
_Loop variables should be declared in the minimal possible scope cpp:S5955_

```c
int32_t k;
for (k=0; k < N; ++k) {
	...
}
```

- Replace this "enum" with "enum class".
_Scoped enumerations should be used cpp:S3642_

- _"using" should be preferred for type aliasing cpp:S5416_

- _"void *" should not be used in typedefs, member variables, function parameters or return type cpp:S5008_

- _Function-like macros should not be used cpp:S960_

- Replace this macro by "const", "constexpr" or an "enum".
_Macros should not be used to define constants cpp:S5028_