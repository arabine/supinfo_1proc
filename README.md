# supinfo_1proc

## Build a program

```
gcc monfichier.c -o monexecutable
```


## Commands related to process management


```
<ctrl+c>: send an interrupt signal to the current process
<ctrl+z>: suspend the current process
bg: resumes suspended jobs in the background
fg: resumes suspended jobs in the foreground

pgrep <executable>: show the process identifier of the given executable name
kill -9 <process id>: send a signal to the specified process id number (9 means really 'kill')
ps: list processes, without options shows the processes for the current shell
```

