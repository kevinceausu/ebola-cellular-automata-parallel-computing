set terminal pngcairo size 1000,700
set output "daySEIRD.png"
plot "data/daySEIRD.dat" u 1:2 w lines title "S", \
     "data/daySEIRD.dat" u 1:3 w lines title "E", \
     "data/daySEIRD.dat" u 1:4 w lines title "I", \
     "data/daySEIRD.dat" u 1:5 w lines title "R", \
     "data/daySEIRD.dat" u 1:6 w lines title "D"

pause -1 "hit return to continue"
