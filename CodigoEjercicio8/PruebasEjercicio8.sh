echo
echo 'Compilacion:'
make
echo
echo 'Ejecutar Test 1 '
echo 'Esperados [ b0 [0.56645], b1 [0.06533], b2 [0.008719], b3 [0.15105], hours [20.76], UPI [26.89], LPI [14.63] ]'
./Ejercicio8 185 150 45 345 65 23 31.4 168 18 18 14.6 94 0 0 6.4 187 185 98 28.3 621 87 10 42.1 255 0 0 15.3
echo
echo 'Ejecutar Test 2 '
echo 'Esperados [ b0 [6.7013], b1 [0.0784], b2 [0.0150], b3 [0.2461], hours [140.9], UPI [179.7], LPI [102.1] ]'
./Ejercicio8 650 3000 155 1142 1060 325 201 863 995 98 98 1065 3205 23 162 554 120 0 54 983 2896 120 138 256 485 88 61
echo
echo
