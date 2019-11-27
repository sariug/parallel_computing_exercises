# Work On Your Figure !

![](doc/lena.jpeg)


Lena is given as a [pgm](https://en.wikipedia.org/wiki/Netpbm_format) format. The reading and the writting functions for the image is already implemented.

#### Tasks :
- Add padding to your image.


- Write a function to apply [convolution](https://en.wikipedia.org/wiki/Kernel_(image_processing)#Convolution).[A website for help](https://www.programming-techniques.com/2013/02/calculating-convolution-of-image-with-c_2.html).

- Use one of the following masks to apply it.

    - Edge detection 

   ![](https://wikimedia.org/api/rest_v1/media/math/render/svg/f800ad5f76b6c26c729ff0c1fef44284d7cade7a)

    - Sharpen

   ![](https://wikimedia.org/api/rest_v1/media/math/render/svg/beb8b9a493e8b9cf5deccd61bd845a59ea2e62cc)

    - Blur

    ![](https://wikimedia.org/api/rest_v1/media/math/render/svg/f1e6d5ec15af752f471372b96a1be4a83e02873e)

- Parallelize the function for desired number of threads and for three cases : 
    - Row wise distribution
    - Column wise distribution
    - Cross distribution

### Example Output
![](doc/example.jpeg)
