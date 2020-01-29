# MPI_Init(NULL, NULL);

### Tasks :

1) Follow the instructions to set up MPI for your OS.(Check this [link!](https://docs.microsoft.com/de-de/archive/blogs/windowshpc/how-to-compile-and-run-a-simple-ms-mpi-program) )

2) Write a "Hello world" for MPI : node 0 send its rank( 0 ) to next rank+1. Each node adds their rank number and prints it out until it reaches back to rank 0. Example:

![alt text](https://i.imgur.com/tklYBKi.png)

3) Do **Ax=B**(Matrix multiplication) with MPI. Let **master** create and distribute a matrix A to **slaves**. Also let **master** provide the vector x. Collected individual **slave** results in **master** and print out the result the result with benchmark(serial) result.   
**Bonus**: Do this for images from the previous classes: Let slaves also communicate eachother for the halo regions.

4) If you made it down until this point, refactor some of the old exercises.
