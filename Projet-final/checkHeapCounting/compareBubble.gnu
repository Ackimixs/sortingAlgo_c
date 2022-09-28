# Set separator of data lines and grid to plot
set datafile separator ";"
set grid

# Set names of stuff
set title "Execution Time vs Complexity bubble sort"
set xlabel "number of elements"
set ylabel "time in milliseconds"

# Set line style, color, width, blabla
set style line 1 linecolor rgb '#ff0000' linetype 1 linewidth 2


# Automatic scaling of axes
set autoscale xy


#### Plot both data and function (data with points)
#TODO COMPLETE FOR COUNRING BAS ET COUNTING AU DESSUS
 plot '/home/acki/CLionProjects/sortingAlgo/Projet-final/checkHeapCounting/counting_sort.csv' title 'counting', '/home/acki/CLionProjects/sortingAlgo/Projet-final/checkHeapCounting/heap_sort.csv' title 'heap'