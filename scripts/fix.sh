#---
# Excerpted from "Test-Driven Development for Embedded C",
# published by The Pragmatic Bookshelf.
# Copyrights apply to this code. It may not be used to create training material, 
# courses, books, articles, and the like. Contact us if you are in doubt.
# We make no guarantees that this code is fit for any purpose. 
# Visit http://www.pragmaticprogrammer.com/titles/jgade for more book information.
#---
DIRS="src tests include unity/LedDriver unity/mocks unity/stdio mocks t0 t1 t2 t3 SandBox"    
#DIRS="unity/AllTests.c"

searchAndDestroy()
{
 #   find $1 -name "$2" | xargs grep -l "$3" | xargs sed -i "" -e "sfind :/\*.*callout.*\*/::g"    
    find $1 -name "$2" | xargs grep -l "$3" | xargs sed -i "" -e $4    
}

removeHeaderComments()
{
    find $1 -name "*.[h]" | xargs grep -l "/////////" | xargs sed -i '' -e '/\/\/\/\//,/\/\/\/\//d'
}

removeCallouts()
{
    searchAndDestroy $1 "*.c" "/\*.*callout id=" "s:/\*.*callout.*\*/::g"
}

plainTextSubtitute()
{
    find $1 -name "$2" | xargs grep -l "$3" | xargs sed -i "" -e "$4"    
}

deleteCppBlockComments()
{
    find $1 -name "*.h" | xargs grep -l "//////////" | xargs sed -i "" -e "/\/\/\/\/\/\/.*\/$/,/\/\/\/\/\/\/.*\/$/d"
 }

addVoidParameter()
{
    find $1 -name "*.[hc]" | xargs grep -lE "^[a-zA-Z]+ [a-zA-Z0-9_]+\(\)" | xargs sed -i "" -E "s/^([a-zA-Z]+ [a-zA-Z0-9_]+)\(\)/\1(void)/g"
 }

for dir in $DIRS
do
    addVoidParameter $dir
done

#textSubtitute $dir "*.$1" "$2" "s/$2/$3/g"
#find $dir -name "*.[hc]" | xargs grep -l "^//-" | xargs sed -i '' -e 's:^//-\(.*$\):/*-\1*/:g'
#    find $dir -name "*.[hc]" | xargs grep -l ".*//[^-]" | xargs sed -i -e 's=\(.*\)//[^-]\(.*\)=\1/* \2 */=g'
#find $dir -name "*.[hc]" | xargs grep -l ".*// *START:" | xargs sed -i "" -e 's=\(.*\)// *START: *\([a-zA-Z0-9_\.]*\)=\1=g'
#find $dir -name "*.[hc]" | xargs grep -l ".*// *END:" | xargs sed -i "" -e 's=\(.*\)// *END: *\([a-zA-Z0-9_\.]*\)=\1=g'
#find . -name "*.[hc]" | xargs grep -l "$1" | xargs sed -i "" -e "s/$1/$2/g"
#find . -name "*.cpp" | xargs grep -l "$1" | xargs sed -i "" -e "s/$1/$2/g"
#find . -name "*.[hc][p]*" | xargs grep -l "[a-z]\*" | xargs sed -i "" -e "s/\([a-z]\)\*/\1 */g" 
