# sample_shell
# TODO: Bug fixes and Unimplemented Subroutines
1. Prompt cursor is not movable
2. echo "/bin/ls" | ./shell
- adds 2 extra newline chars that print 2 invalid dollar signs when run
3. command such as id/ls when run provides proper output
but when you input a command that does not exist it will run the previous command.
example:
$ ls
Alx sample.c a.c
$ kk
Alx sample.c a.c

# the second command should have printed "command not found"

4. Execute commands only take in 2 arguments if 3 or more arguments are used the command fails e.g
$ ls -a -l
# Fix for this can be to check and modify the function
execute_command() that is in main.c
# will fail
5. Environment commands preceded by a dollar sign are not yet expandable - "Unimplemented"
# fix for this is to implement a search for the $ char then expand and save it to array queue struct pOp using the command function enqueue(struct op_t, char *str)

6. passing of environment variable to the shell is unimplemented thus the execution of :
$env
# does not return anything since.
7. Program sourcecode is non Betty compliant.
