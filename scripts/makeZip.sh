#---
# Excerpted from "Test-Driven Development for Embedded C",
# published by The Pragmatic Bookshelf.
# Copyrights apply to this code. It may not be used to create training material, 
# courses, books, articles, and the like. Contact us if you are in doubt.
# We make no guarantees that this code is fit for any purpose. 
# Visit http://www.pragmaticprogrammer.com/titles/jgade for more book information.
#---
#/bin/sh -x
#run from Book/code

zipDir=code/tmp
zipIt() {
    releaseName=$1
    dateVersion=$2
    otherZipOptions=$3
    zip -r $zipDir/${releaseName}-${dateVersion}.zip \
           code \
           -x@code/scripts/zipExclude.txt\
    	   -x \*CppUTest/platforms/\*
}


generateZip() {
    dateVersion=$(date +%F-%H-%M)
    zipName=$1
    otherZipOptions=$2
    zipIt $zipName $dateVersion
}

cd ..
mkdir -p $zipDir
generateZip BookCode
cd code


