#!/bin/bash
#---------------------------------------------------
#usage:
#./test_MODEX <input-dir> <instances-list>

path=`pwd`
echo "pwd: $path"

result=$path"/results.txt"
echo "Result is presented in: $result"

source=$path"/"$1
echo "Input directory is: $source"

list=$path"/"$2
echo "Instances to be checked are presented in: $list"

if [ ! -n "$1" ]
then
	echo "usage: ./TestPT.sh <execfilename> <input-dir> <instances-list>"
	echo "TestPT.sh, <execfilename>, <input-dir>, <instances-list> should be in the same directory"
elif [ ! -n "$2" ]
then
	echo "usage: ./TestPT.sh <execfilename> <input-dir> <instances-list>"
	echo "TestPT.sh, <execfilename>, <input-dir>, <instances-list> should be in the same directory"
else
	for line in `cat $list`
	do
    	flag=0
    	name=$line
	#echo $name
	
    	for element in `ls $source` 
    	do  
 		if [ $name == $element ]    
		then
			instance_name=${line%.*}

			./verify $1/$line |tee -a $result

			flag=1
			break
		fi
    	done
		if [ $flag -eq 0 ]
		then
			echo "Input:$line  does not exist"
		fi
	done
fi
