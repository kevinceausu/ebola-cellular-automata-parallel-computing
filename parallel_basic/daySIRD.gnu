set terminal pngcairo size 1000,700
set output "daySIRD.png"
plot "data/daySIRD.dat" u 1:2 w lines title "S", "data/daySIRD.dat" u 1:3 w lines title "I", "data/daySIRD.dat" u 1:4 w lines title "R", "data/daySIRD.dat" u 1:5 w lines title "D"
pause -1 "hit return to continue"
