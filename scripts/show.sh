#---
# Excerpted from "Test-Driven Development for Embedded C",
# published by The Pragmatic Bookshelf.
# Copyrights apply to this code. It may not be used to create training material, 
# courses, books, articles, and the like. Contact us if you are in doubt.
# We make no guarantees that this code is fit for any purpose. 
# Visit http://www.pragmaticprogrammer.com/titles/jgade for more book information.
#---
echo "-------------------------------------------------------------------------"
echo 
echo 
echo 
echo 
echo 
echo 
echo 
echo 
echo 

DIRS="src tests include unity/LedDriver unity/mocks unity/stdio mocks t0 t1 t2 t3 SandBox"    

for dir in $DIRS
do
    find $dir -name "$1" | xargs grep -E "$2" 
done

#find . -name "*.cpp" | xargs grep "$1" 
