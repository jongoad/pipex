# pipex

A minimal recreation of the shell operator pipe, written in C.
<br></br>
## Description
Pipex is a 42 cursus solo project designed to introduce the concepts of parallel processes, including the use of fork(), pipe()  and execve(). It involves recreating most of the functionality of the shell operator pipe ('|'), including mangaging signal piping and IO redirection. In addition it introduces the concept of here_doc and how to read input from STDIN. As with many 42 cursus projects, very few libraries and functions are allowed. The allowed functions for this project are:

- `open(), close(), read(), write(), malloc(), free(), perrer(), strerror(), access(), dup(), dup2()`
- `execve(), exit(), fork(), pipe(), unlink(), wait(), waitpid()`

In addition, any functions previously written from scratch in previous projects are allowed if included in your libft library.

A full description can be found in the [subject](subject/en.subject.pdf) pdf.
<br></br>
## Usage
The program runs in a very similar manner to the shell implementation, however it does not use the same syntax. Pipex can be run using the following syntax (command and arguments must be wrapped in quotes):
```bash
$> ./pipex file1 cmd1 cmd2 file2

$> < file1 cmd1 | cmd2 file2 >
```

## Bonus Section

The bonus section of pipex involves handling multiple pipes in a single line, as well as handling inpur redirection from here_doc. The syntax for using the bonus is as follows:

Use here_doc for input:
```bash
$> ./pipex_bonus here_doc LIMITER cmd1 cmd2 cmd3 file2

$> cmd1 << LIMITER | cmd2 | cmd3 | >> file2
```
Use multiple pipes:
```bash
$> ./pipex_bonnus file1 cmd1 cmd2 cmd3 file2

$> < file1 cmd1 | cmd2 | cmd3 file2 >
```
## Final Grade
![125/100](img/125.png)