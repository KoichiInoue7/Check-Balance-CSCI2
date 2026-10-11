# Bracket Balance Checker (C++)

A C++ program that reads a source code file and checks whether its brackets
`( )`, `{ }` and `[ ]` are correctly matched, and reports where they aren't.
Built for CSCI 2 (Project 4) to practise using **stacks**.

## How it works

The program reads the file one character at a time:

- **Opening bracket** `(` `{` `[` → pushed onto a `std::stack`, along with its line number
- **Closing bracket** `)` `}` `]` → must match the bracket on top of the stack, otherwise
  the file is unbalanced
- **End of file** → if anything is still on the stack, something was never closed, and the
  program reports the line where it was opened

It also skips over the parts of code where brackets don't count:

- `// line comments` and `/* block comments */`
- `"string literals"` and `'character literals'`, including escaped quotes like `\"`

so a `{` inside a string or a comment doesn't break the check. It also reports
quotes that are never closed.

## Build and run

```bash
g++ -std=c++17 Project4/balance.cpp -o balance
./balance
```

Enter the name of a file to check when asked. Three test files are included in
`Project4/`:

| file | result |
|---|---|
| `good_balance.cpp` | `Parentheses match` → `balance ok` |
| `bad_balance.cpp` | `Unmatched } symbol at line 14`: the `{` opened on line 14 is never closed |
| `bad_balance2.cpp` | `Missing '  on line 16`: an unclosed character quote |

Or open `Project4.sln` in Visual Studio.

## What I learned

- Why a **stack** is the natural tool for matching pairs: the most recent opening
  bracket is always the one the next closing bracket has to match
- Reading a file character by character, and keeping track of "state" (am I inside a
  comment? inside a string?) while doing it
