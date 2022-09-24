for dir in */; do
	cd $dir
    gnuplot *.gnu
	cd ..
done
