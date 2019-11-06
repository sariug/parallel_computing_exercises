
# Tasks 

1- Write a function that takes two arrays and array size and returns the [norm](http://mathworld.wolfram.com/L2-Norm.html) of the function. 

2- Test your function ! 
- Make sure that the answer is correct. (Either hand calculate for 3 times(for positive, negative and zero containing arrays) or utilize the cpp [_inner_product_](https://en.cppreference.com/w/cpp/algorithm/inner_product) function )
- Make sure it does not crash for wrong input (such as if array sizes are not equal, or any array does not contain a null pointer.)


2- Try your function with arrays with the length of [1e2, 1e3, 1e4, 1e5, 1e6, 1e7]. Plot the duration of each call. What do you see ? 

3- Try your function with different flags -o0, -o1, -o2, -o3. Do you see any difference ? 

**Bonus** : Calculate number of floating point operating(FLOPS) for your _norm_ implementation. 

4- How can you paralelize this ?

5 - Paralelize this routine using _threads_. Get help from last weeks assignments. 

6 - Do second and third assignments for the parallelized script. 

7 - Compare parallel to no-parallel speed (in terms of milliseconds) with respect to number of threads and size of the array used. 


## Prize
The author of the best scaled function earns a **BEER** !
