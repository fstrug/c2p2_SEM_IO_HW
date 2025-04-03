# Solutions

## Day 1
1) It is expected that compression factors should increase for data as the range of values it can take on decrease and the randomness of those values decrease. I would expect disk usage and CPU wall time to be largest for random datasets over large ranges with no patterns for lossless compression algorithms. Disk usage is increased because it is not possible to decrease the size of the bytestream. CPU wall time would increase as the algorithm would need to exhaust all potential methods of compressing the bytestream before determining it is not possible.
2) See histograms below.
3) Answers below
	1) Only random floating point numbers result shown in first plot with 'vpx'. All the numbers are random floats and we can see their is little effect on basket size. We potentially gain increased compression factors for increased basket sizes. However, the compression factor increases from 1.09 to 1.10 from a basket size of 4 kb to 1024 kb.	
	   
	   In the second plot, we see results for the compression factor of 'vpt' and 'vpint'. The vpt branch is a series of random numbers calculated from vpx and vpy thats repeat twice each time (ex. 2,2,1,1,7,7,3,3, etc.). This can explain why we see a large improvement in compression factor overall when compared to vpx. Since there are many small and potentially large-scale patterns we get better compression. Increasing the basket-size marginally increases the compression factor. Vpint is the most compressible of the branches due to the fact it takes on the narrowest range of values. For `vecsize=100`, vpint is the set of integers between 0 and 100. Vpx is a float generated from a Gaussian distribution, so it is unlikely for some number to be generated twice - particularly in sequence.
	2) For smaller basket sizes, generally the compression factor decreases. Over smaller byte-ranges there are less potential patterns for the compression algorithm to recognize and compress by. As basket size increases, the algorithm sees more of the full dataset. 
	   
	   Also, compression factors cannot exceed the basket size itself. So larger basket sizes have higher potential compression factors.
	   
	   There do not seem to be any other obvious changes brought about by varying basket size. In plot 3, we plot the runtime as a function of basket size and there are no apparent patterns to be found.
	3) The benchmarks give us insight into what factors affect how well (or poorly) some type of data can be compress. It also can be used to measure how compression factors, run times, and CPU times may vary between releases for the same or similarly structured datasets. 

## Day 2
