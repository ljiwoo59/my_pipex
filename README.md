# my_pipex
Code UNIX mechanism

* The execution will be as same as the following shell command:
```
< file1 cmd1 | cmd2 > file2
```
* **cmd1** takes **file1** as an input, and **cmd2** takes an output of **cmd1** as an input, then returns an output to **file2**

## Used functions

#### *int open(const char *path, int oflag, ...);*
* Opens **file1** with *O_RDONLY* flag
* Opens **file2** with *O_WRONLY*, *O_CREAT*, *O_TRUNC* giving file permission as **666**
  - *O_CREAT* : *file2* will be created if there has no such file
  - *O_TRUNC* : if *file2* already exists, *file2* will be truncated size to 0
* Returns non-negative file descriptor if successful, otherwise returns -1 with *errno*
  
#### *int close(int fildes);*
* Deletes a descriptor
* Returns 0 if successful, otherwise returns -1 with *errno*

#### *pid_t waitpid(pid_t pid, int *stat_loc, int options);*
* Waits for certain child processes
  - **pid** : specifies the set of child processes for which to wait
  - **stac_loc** : contains termination information about the process that exited
  - **options** : WNOHANG option, WUNTRACED option *(man 2 waitpid)*
* Returns pid of child process if child process is stopped or terminated, otherwise returns -1 with *errno*

#### *int pipe(int fildes[2]);*
* Creates a **pipe** with unidirectional data flow and allocates a pair of file descriptors
* Allows the output of one program to be sent to another program
* Data written to fildes[1] can be read from fildes[0]
  - fildes[0] : output
  - fildes[1] : input
* Returns 0 if successful, otherwise returns -1 with *errno*

#### *int dup2(int fildes, int fildes2);*
* Duplicates fildes to fildes2
* Returns the new file descriptor, otherwise returns -1 with *errno*

#### *int execve(const char *path, char *const argv[], char *const envp[]);*
* Overlays the current process images to new process image
  - **path** : indicates executable object file or file of data for an interpreter
  - **argv** : the argument lists to be made available to the new process
    - the first element should be the name of executed program
  - **envp** : Passes information to the new process that is not directly an argument to the command
* Successful call has no process to return to, otherwise returns to the calling process with *errno*

#### *pid_t fork(void);*
* Creates child process as an exact copy of the callling process
* Returns 0 to the child process and returns pid of the child process to the parent process, otherwise returns -1 with *errno*

#### *void perror(const char *s);*
* Finds the error message corresponding to the current value of the global variable *errno* and writes it followed by a new line

#### *char *strerror(int errnum);*
* Accepts an error number argument *errnum* and returns a pointer to the corresponding message string


## Implemetation
* Argument numbers should be 5
* Guard all functions to return error message and exit when fail to execute

### Step 1
* Using pipe(), create a pipe
* Using fork(), create a *child process*

### Step 2
* Both parent and child processes are running
* *Parent process* opens/creates **file2** and sets file descriptor of STDOUT_FILENO as that of **file2**
* *Parent process* will get an output as an **input** from pipe by setting fildes[0] as STDIN_FILENO
* *Parent process* then waits child process to be terminated
* *Child process* opens **file1** and sets file descriptor of STDIN_FILENO as that of **file1**
* *Child process* will send **output** to pipe by setting fildes[1] as STDOUT_FILNO
* *Child process* will execute the first command and will be terminated
* *Parent process* will execute the second command and will be terminated

### Processing commands
* Since the path of shell commands are variable, try each path with specific command (if no such directory or file, return error)
* To know if *Child process* is abnormally exited, use WIFEXITED() with status of *Child process*
