# OpenMP Exercises

### Tasks :

1) Welcome to OpenMP:
    - Set number of threads [4:12]
    - Make the thread say "Hello Boss ! This is thread number %d". 
2) Numerical Integration:
    - "Compute π by numerical integration . We use the fact that π is the area of the unit circle, and we approximate this by computing the area of a quarter circle using Riemann sums." 
    - "Let f(x)=√(1−x^2) be the function that describes the quarter circle for x=0…1"
    - "Then we compute π/4≈∑Δxf(xi) where xi=iΔx and Δx=1/N"
    - First write it in serial then with OMP. Benchmark it.
3) Finding bounding box
    - Generate N number of **random** coordinates(x,y,z).
    - Find minx, miny, minz, maxx,maxy,maxz using __old way__.
    - Find above again parallelly with OMP.
Do it on your own branch and create a pull request !
