#!/bin/sh

# Regression testing script for DaMPL Compiler
# Step through a list of files
#  Compile, run, and check the output of each expected-to-work test
#  Compile and check the error of each expected-to-fail test

# Path to C Compiler (GCC)
GCC="gcc"
LDFLAG="-g -Llibs/"
CFLAG="-Ilibs/"
LDLIB="-ldampllib"
#GCC="usr/bin/gcc"

# DaMPL compiler.
DAMPLC="./dampl"

# Test files
files="tests/*.mpl"

Greetings() {
	echo ""
	echo "\t/*DaMPL Automated Test Script */"
}

Build() {
	echo ""
	echo "Building the DaMPL Compiler ..."
	cd src &&
	make &&
	cp dampl ../dampl 
	cd ..
	cd libs &&
	make &&
	cd ..
	echo "Done."
}

Test() {
	if [ -s files_to_check.txt ]; then
		rm files_to_check.txt
	fi

	echo "These files presented different output than expected during the automated test.\n" >> files_to_check.txt

	for file in $files
	do
		echo ""

		filename="${file%.*}"
		echo "File: \"${file}\""
		echo "Compiling from .mpl to .c ..."
		eval "$DAMPLC" "${file}" ">" "${filename}.c" "2> ./tests/temp.out"

		if [ -s ./tests/temp.out ]
		then
	    	echo "Compile time error detected ..."

	    	diff -b ${filename}.out ./tests/temp.out > ${filename}.diff 2>&1
			rm ./tests/temp.out

			if [ -s ${filename}.diff ]
			then
				echo "WARNING: Output differs from expected."
				echo "${filename}\n" >> files_to_check.txt
			fi
	    	
	    	echo "Done."
	    	continue
		else 
			echo "Generating the executable file ..."
			eval "$GCC" "-o" "${filename}" "${filename}.c" "$CFLAG" "$LDFLAG" "$LDLIB"

			echo "Testing the generated file ..."
			./${filename} > ./tests/temp.out 2>&1

			diff -b ${filename}.out ./tests/temp.out > ${filename}.diff 2>&1

			if [ -s ${filename}.diff ]
			then
				echo "WARNING: Output differs from expected."
				echo "${filename}\n" >> files_to_check.txt
			fi

			rm ./tests/temp.out
			rm ${filename}

			echo "Done."
		fi
	done
}

# Main #

# Builds the compiler
Greetings
Build
Test