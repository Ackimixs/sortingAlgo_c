# Set separator of data lines and grid to plot
set datafile separator ";" 
set grid

# Set names of stuff
set title "Execution Time vs Complexity Counting Sort log"
set xlabel "number of elements"
set ylabel "time in milliseconds"

# Set line style, color, width, blabla
set style line 1 linecolor rgb '#ff0000' linetype 1 linewidth 2
set style line 2 linecolor rgb '#00ff00' linetype 1 linewidth 2

#### Prepare the function
f(x) = c * ((log(x)) + x )

#### Fit the function to data 
fit f(x) '/home/acki/Documents/Projet-final/counting_sortlog/counting_sort_log.csv' via c

# Save value of c to show in the function

title_f(c) = sprintf("f(x) = c*(log(n)+n), c = %f", c)

# Automatic scaling of axes
set autoscale xy


#### Plot both data and function (data with points)
 plot '/home/acki/Documents/Projet-final/counting_sortlog/counting_sort_log.csv' title 'data', f(x) title title_f(c) with lines linestyle 2
