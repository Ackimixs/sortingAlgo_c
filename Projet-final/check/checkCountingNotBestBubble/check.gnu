# Set separator of data lines and grid to plot
set datafile separator ";"
set grid

# Set names of stuff
set title "Execution Time vs Complexity bubble vs counting k big"
set xlabel "number of elements"
set ylabel "time in milliseconds"

# Set line style, color, width, blabla
set style line 1 linecolor rgb '#ff0000' linetype 1 linewidth 2


# Automatic scaling of axes
set autoscale xy


#### Plot both data and function (data with points)
 plot '/home/acki/CLionProjects/sortingAlgo/Projet-final/check/checkCountingNotBestBubble/counting_sort.csv' title 'counting worst', '/home/acki/CLionProjects/sortingAlgo/Projet-final/check/checkCountingNotBestBubble/bubble_sort.csv' title 'bubble V2 normal', '/home/acki/CLionProjects/sortingAlgo/Projet-final/check/checkCountingNotBestBubble/heap_sort.csv' title 'heap'