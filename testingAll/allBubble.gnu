# Set separator of data lines and grid to plot
set datafile separator ";"
set grid

# Set names of stuff
set title "Execution Time vs Complexity all bubble"
set xlabel "number of elements"
set ylabel "time in milliseconds"

# Set line style, color, width, blabla
set style line 1 linecolor rgb '#ff0000' linetype 1 linewidth 2


# Automatic scaling of axes
set autoscale xy


#### Plot both data and function (data with points)
 plot '/home/acki/CLionProjects/sortingAlgo/testingAll/bubble_sort.csv' title 'bubble sort', '/home/acki/CLionProjects/sortingAlgo/testingAll/bubbleV2_sort.csv' title 'bubble v2 sort', '/home/acki/CLionProjects/sortingAlgo/testingAll/bubbleV2_ascending_sort.csv' title 'bubble v2 ascending sort',  '/home/acki/CLionProjects/sortingAlgo/testingAll/bubbleV2_descending_sort.csv' title 'bubble v2 descending sort'