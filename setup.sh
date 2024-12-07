
cd /Users/admin/Documents/Projects/yacpplr/aoc2024/
${1?"Usage: $0 {Day Num}"}

mkdir day_$1
cp template/main.cpp day_$1
cd day_$1

echo "name = day_$1" > Makefile 

echo '
main: main.cpp
	g++ main.cpp -o $(name) -Wall -Werror -Wuninitialized -std=c++23
run: main
	./$(name)' >> Makefile

touch input.txt
touch test.txt


code .
echo "Day $1 setup complete"