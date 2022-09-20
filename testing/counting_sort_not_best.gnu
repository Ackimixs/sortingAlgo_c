# Set separator of data lines
set datafile separator ";" 
set grid

# Set names of stuff
set title "Execution Time vs Complexity"
set xlabel "number of elements"
set ylabel "time in milliseconds"

# Set line style, color, width, blabla
set style line 1 linecolor rgb '#ff0000' linetype 1 linewidth 2
set style line 2 linecolor rgb '#00ff00' linetype 1 linewidth 2

#### Prepare the function
c = 0.00000000015	# to fit with the data !
f(x) = c * x*100000+0.39

title_f(c) = sprintf("f(x) = c*n*100000+0.39, c = %f", c)

# Automatic scaling of axes
set autoscale xy

#### Plot data only
# plot '/home/acki/Documents/Projet-final-20220919/counting_sort_not_best.csv' title 'data'

#### Plot both data and function (data with continuous line)
# plot '/home/acki/Documents/Projet-final-20220919/counting_sort_not_best.csv' title 'data' with lines linestyle 1, f(x) title title_f(c) with lines linestyle 2

#### Plot both data and function (data with points)
 plot '/home/acki/Documents/Projet-final-20220919/counting_sort_not_best.csv' title 'data', f(x) title title_f(c) with lines linestyle 2
