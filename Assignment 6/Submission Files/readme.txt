Joel George
004786402

I had a hard time with this lab, because I tried to parallelize the ray
generating section of the three-level-deep nested for loop in main. I was trying
to parallelize this section of the code:

for(int ys =- halfSamples; ys <=halfSamples; ++ys)
{

	double subx = x + ((double)xs)*subsample_dx;
	double suby = y + ((double)ys)*subsample_dy;

	ray_t pixel_ray;
	copy( pixel_ray.org ,camera_pos);
	Vec3 pixel_target;
	set( pixel_target, subx, suby, z);
	sub( pixel_ray.dir, pixel_target, camera_pos);
	norm( pixel_ray.dir, pixel_ray.dir );

	Vec3 sample_color;
	copy( sample_color, bg_color );
	trace( &scene, sample_color, &pixel_ray, 0 );
	add( pixel_color, pixel_color, sample_color );

}

This was a bad choice to parallelize for multiple reasons. Firstly, this section
of the code relies on many variables outside of its current scope. Since
pthread_create runs an external function, the variables that are outside of its
scope (subsample_dx, subsample_dy, camera_pos, z, bg_color, scene) must be
passed in. However, pthread_create only accepts one argument for its function,
so I had to create a struct, copy in every variable as a data field of that
struct, and pass a pointer to that struct to pthread_create. Not only is this
inefficient, but it actually made my code crash many times, because the
variables were being passed by value, not by reference, and so when later
sections of the code ran, I would either get a segmentation fault or the output
would not be the correct output. Instead of going in and finding out which
variables required to be passed by reference and which ones didn't, I
parallelized the whole nested for loop situation, copying almost all of main
into an external function. This neatly dealt with the problem of variable
handling. 

I ran into problems when passing in my first argument into the pthread_create
function, so I had to create another array to hold each thread number, and then
accessed that array to pass in the respective number of the thread to the
pthread_create function. This thread number helped guide the flow of the work,
to make sure that the threads were actually splitting up the work and were not
repeating work that was done by another thread. 

In terms of speed, the multithreaded program ran way faster than the normal
one. There was a linear relationship exhibited between the number of threads and
the time it took for that number of threads to execute the program. Unlike in
the lab section, multithreading clearly sped up the program. These were the
output time stamps:

1 thread:
real    1m6.277s
user    1m6.246s
sys     0m0.005s

2 threads:
real    0m35.197s
user    1m7.821s
sys     0m0.011s

4 threads:
real    0m19.128s
user    1m13.823s
sys     0m0.006s

8 threads:
real    0m10.465s
user    1m15.963s
sys     0m0.011s

It is clear to see that in every field of time (real, user, and sys), the more
threads there were, the faster the program ran. 
