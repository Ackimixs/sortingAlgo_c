for dir in */; do
    gnuplot $dir/*.gnu -psersist
done
