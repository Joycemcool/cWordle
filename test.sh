returnStatus=0

# Only show colours on local "Git Bash" terminal
passFormat="if [ $TERM = "xterm" ]; then tput sgr0 && tput setaf 2; fi"
failFormat="if [ $TERM = "xterm" ]; then tput sgr0 && tput setaf 1; fi"
normalFormat="if [ $TERM = "xterm" ]; then tput sgr0; fi"

# If not on Linux set output to .exe
unameValue="$(uname -s)"
echo "Testing OS Platform: $unameValue"
fileExtension=".exe"
if [  $unameValue = "Linux" ] || [  $unameValue = "Darwin" ] ; then
    fileExtension=".out"
fi

echo "Running tests..."
echo

./a$fileExtension > /dev/null 2>&1

if [ $? -eq 1 ] ; then
  eval "$passFormat"
  echo "Pass: Program exited with correct error code"
else
  eval "$failFormat"
  echo "Fail: Program did not exit with correct error code"
  returnStatus=1
fi

output_1=$(./a$fileExtension 2>&1)

# don't worry about extra whitespace in the output
newOutput_1=""
while read line
do
  newOutput_1=$newOutput_1$(echo "$line" | xargs)
done <<< "$output_1"

expected_output_1="Invalid number of command line arguments."

# Use contains so we ignore additional output or input prompts
if grep -q "$expected_output_1" <<< "$newOutput_1"; then
  eval "$passFormat"
  echo "Test #1 - No Args - Pass: Output is correct"
else
  eval "$failFormat"
  echo "Test #1 - No Args - Expected '$expected_output_1' but got: $newOutput_1"
  returnStatus=1
fi

echo

./a$fileExtension apple banana cucumber donut egg  > /dev/null 2>&1

if [ $? -eq 1 ] ; then
  eval "$passFormat"
  echo "Pass: Program exited with correct error code"
else
  eval "$failFormat"
  echo "Fail: Program did not exit with correct error code"
  returnStatus=1
fi

output_2=$(./a$fileExtension apple banana cucumber donut egg 2>&1)

# don't worry about extra whitespace in the output
newOutput_2=""
while read line
do
  newOutput_2=$newOutput_2$(echo "$line" | xargs)
done <<< "$output_2"

expected_output_2="Invalid number of command line arguments."

# Use contains so we ignore additional output or input prompts
if grep -q "$expected_output_2" <<< "$newOutput_2"; then
  eval "$passFormat"
  echo "Test #2 - Wrong Args Count - Pass: Output is correct"
else
  eval "$failFormat"
  echo "Test #2 - Wrong Args Count - Expected '$expected_output_2' but got: $newOutput_2"
  returnStatus=1
fi

echo

./a$fileExtension apple banana cucumber donut > /dev/null 2>&1

if [ $? -eq 1 ] ; then
  eval "$passFormat"
  echo "Pass: Program exited with correct error code"
else
  eval "$failFormat"
  echo "Fail: Program did not exit with correct error code"
  returnStatus=1
fi

output_3=$(./a$fileExtension apple banana cucumber donut 2>&1)

# don't worry about extra whitespace in the output
newOutput_3=""
while read line
do
  newOutput_3=$newOutput_3$(echo "$line" | xargs)
done <<< "$output_3"

expected_output_3="Invalid command line argument usage."

# Use contains so we ignore additional output or input prompts
if grep -q "$expected_output_3" <<< "$newOutput_3"; then
  eval "$passFormat"
  echo "Test #3 - Wrong Args Format #1 - Pass: Output is correct"
else
  eval "$failFormat"
  echo "Test #3 - Wrong Args Format #1 - Expected '$expected_output_3' but got: $newOutput_3"
  returnStatus=1
fi

echo

./a$fileExtension -i banana cucumber donut > /dev/null 2>&1

if [ $? -eq 1 ] ; then
  eval "$passFormat"
  echo "Pass: Program exited with correct error code"
else
  eval "$failFormat"
  echo "Fail: Program did not exit with correct error code"
  returnStatus=1
fi

output_4=$(./a$fileExtension -i banana cucumber donut 2>&1)

# don't worry about extra whitespace in the output
newOutput_4=""
while read line
do
  newOutput_4=$newOutput_4$(echo "$line" | xargs)
done <<< "$output_4"

expected_output_4="Invalid command line argument usage."

# Use contains so we ignore additional output or input prompts
if grep -q "$expected_output_4" <<< "$newOutput_4"; then
  eval "$passFormat"
  echo "Test #4 - Wrong Args Format #2 - Pass: Output is correct"
else
  eval "$failFormat"
  echo "Test #4 - Wrong Args Format #2 - Expected '$expected_output_4' but got: $newOutput_4"
  returnStatus=1
fi

echo

./a$fileExtension -i banana -o donut > /dev/null 2>&1

if [ $? -eq 1 ] ; then
  eval "$passFormat"
  echo "Pass: Program exited with correct error code"
else
  eval "$failFormat"
  echo "Fail: Program did not exit with correct error code"
  returnStatus=1
fi

output_5=$(./a$fileExtension -i banana -o donut 2>&1)

# don't worry about extra whitespace in the output
newOutput_5=""
while read line
do
  newOutput_5=$newOutput_5$(echo "$line" | xargs)
done <<< "$output_5"

expected_output_5="Cannot open banana for reading."

# Use contains so we ignore additional output or input prompts
if grep -q "$expected_output_5" <<< "$newOutput_5"; then
  eval "$passFormat"
  echo "Test #5 - Bad Input File - Pass: Output is correct"
else
  eval "$failFormat"
  echo "Test #5 - Bad Input File - Expected '$expected_output_5' but got: $newOutput_5"
  returnStatus=1
fi

echo

./a$fileExtension -i ./test-files/word1.txt -o ./nonfolder/out1.txt > /dev/null 2>&1

if [ $? -eq 1 ] ; then
  eval "$passFormat"
  echo "Pass: Program exited with correct error code"
else
  eval "$failFormat"
  echo "Fail: Program did not exit with correct error code"
  returnStatus=1
fi

output_6=$(./a$fileExtension -i ./test-files/word1.txt -o ./nonfolder/out1.txt 2>&1)

# don't worry about extra whitespace in the output
newOutput_6=""
while read line
do
  newOutput_6=$newOutput_6$(echo "$line" | xargs)
done <<< "$output_6"

expected_output_6="Cannot open ./nonfolder/out1.txt for writing."

# Use contains so we ignore additional output or input prompts
if grep -q "$expected_output_6" <<< "$newOutput_6"; then
  eval "$passFormat"
  echo "Test #6 - Bad Output File - Pass: Output is correct"
else
  eval "$failFormat"
  echo "Test #6 - Bad Output File - Expected '$expected_output_6' but got: $newOutput_6"
  returnStatus=1
fi

echo

# START OF 'WORKING' TEST CASES

./a$fileExtension -i ./test-files/word1.txt -o ./test-files/game-result1.txt > /dev/null 2>&1 <<'EOF'
least
pound
SOUND
STATE
later
tower
EOF

if [ $? -eq 0 ] ; then
  eval "$passFormat"
  echo "Pass: Program exited zero"
else
  eval "$failFormat"
  echo "Fail: Program did not exit zero"
  returnStatus=1
fi

output_7=$(cat ./test-files/game-result1.txt)

# don't worry about extra whitespace in the output
newOutput_7=""
while read line
do
  newOutput_7=$newOutput_7$(echo "$line" | xargs)
done <<< "$output_7"

expected_output_7="The solution was not found."

# Use contains so we ignore additional output or input prompts
if grep -q "$expected_output_7" <<< "$newOutput_7"; then
  eval "$passFormat"
  echo "Test #7 - Word #1 File - Unsolved - Pass: Output is correct"
else
  eval "$failFormat"
  echo "Test #7 - Word #1 File - Unsolved - Expected '$expected_output_7' but got: $newOutput_7"
  returnStatus=1
fi

echo

./a$fileExtension -o ./test-files/game-result2.txt -i ./test-files/word1.txt > /dev/null 2>&1 <<'EOF'
abc
LEAST
!@#$%
excessive
WORDS
test1
SHOCK
SMOKY
EOF

if [ $? -eq 0 ] ; then
  eval "$passFormat"
  echo "Pass: Program exited zero"
else
  eval "$failFormat"
  echo "Fail: Program did not exit zero"
  returnStatus=1
fi

output_8a=$(./a$fileExtension -o ./test-files/game-result2.txt -i ./test-files/word1.txt 2>&1 <<'EOF'
abc
LEAST
!@#$%
excessive
WORDS
test1
SHOCK
SMOKY
EOF
)

# don't worry about extra whitespace in the output
newOutput_8a=""
while read line
do
  newOutput_8a=$newOutput_8a$(echo "$line" | xargs)
done <<< "$output_8a"

output_8b=$(cat ./test-files/game-result2.txt)

# don't worry about extra whitespace in the output
newOutput_8b=""
while read line
do
  newOutput_8b=$newOutput_8b$(echo "$line" | xargs)
done <<< "$output_8b"

expected_output_8a="Sorry, but you can only enter 5-letter words."
expected_output_8b="The solution was found."

# Use contains so we ignore additional output or input prompts
if grep -q "$expected_output_8a" <<< "$newOutput_8a"; then
  if grep -q "$expected_output_8b" <<< "$newOutput_8b"; then
    eval "$passFormat"
    echo "Test #8 - Word #1 File - Solved with Invalid Entries - Pass: Output is correct"
  else
    eval "$failFormat"
    echo "Test #8 - Word #1 File - Solved with Invalid Entries - Expected '$expected_output_8b' but got: $newOutput_8b"
    returnStatus=1
  fi
else
  eval "$failFormat"
  echo "Test #8 - Word #1 File - Solved with Invalid Entries - Expected '$expected_output_8a' but got: $newOutput_8a"
  returnStatus=1
fi

echo

./a$fileExtension -i ./test-files/word2.txt -o ./test-files/game-result3.txt > /dev/null 2>&1 <<'EOF'
strong
pastry
trades
travel
EOF


if [ $? -eq 0 ] ; then
  eval "$passFormat"
  echo "Pass: Program exited zero"
else
  eval "$failFormat"
  echo "Fail: Program did not exit zero"
  returnStatus=1
fi

output_9=$(cat ./test-files/game-result3.txt)

# don't worry about extra whitespace in the output
newOutput_9=""
while read line
do
  newOutput_9=$newOutput_9$(echo "$line" | xargs)
done <<< "$output_9"

expected_output_9="The solution was found."

# Use contains so we ignore additional output or input prompts
if grep -q "$expected_output_9" <<< "$newOutput_9"; then
  eval "$passFormat"
  echo "Test #9 - Word #2 File - Solved - Pass: Output is correct"
else
  eval "$failFormat"
  echo "Test #9 - Word #2 File - Solved '$expected_output_9' but got: $newOutput_9"
  returnStatus=1
fi

echo

./a$fileExtension -o ./test-files/game-result4.txt -i ./test-files/word3.txt  > /dev/null 2>&1 <<'EOF'
spot
TAIL
then
TEMP
tube
EOF

if [ $? -eq 0 ] ; then
  eval "$passFormat"
  echo "Pass: Program exited zero"
else
  eval "$failFormat"
  echo "Fail: Program did not exit zero"
  returnStatus=1
fi

output_10=$(cat ./test-files/game-result4.txt)

# don't worry about extra whitespace in the output
newOutput_10=""
while read line
do
  newOutput_10=$newOutput_10$(echo "$line" | xargs)
done <<< "$output_10"

expected_output_10="The solution was not found."

# Use contains so we ignore additional output or input prompts
if grep -q "$expected_output_10" <<< "$newOutput_10"; then
  eval "$passFormat"
  echo "Test #10 - Word #3 File - Unsolved - Pass: Output is correct"
else
  eval "$failFormat"
  echo "Test #10 - Word #3 File - Unsolved - Expected '$expected_output_10' but got: $newOutput_10"
  returnStatus=1
fi

echo

./a$fileExtension -i ./test-files/word4.txt -o ./test-files/game-result5.txt > /dev/null 2>&1 <<'EOF'
least
drone
drain
order
radar
later
Hater
CODER
EOF


if [ $? -eq 0 ] ; then
  eval "$passFormat"
  echo "Pass: Program exited zero"
else
  eval "$failFormat"
  echo "Fail: Program did not exit zero"
  returnStatus=1
fi

output_11=$(cat ./test-files/game-result5.txt)

# don't worry about extra whitespace in the output
newOutput_11=""
while read line
do
  newOutput_11=$newOutput_11$(echo "$line" | xargs)
done <<< "$output_11"

expected_output_11="The solution was found."

# Use contains so we ignore additional output or input prompts
if grep -q "$expected_output_11" <<< "$newOutput_11"; then
  eval "$passFormat"
  echo "Test #11 - Word #4 File - Solved - Pass: Output is correct"
else
  eval "$failFormat"
  echo "Test #11 - Word #4 File - Solved '$expected_output_11' but got: $newOutput_11"
  returnStatus=1
fi

echo

rm ./test-files/game-result*

if [ $returnStatus -eq 0 ] ; then
    eval "$passFormat"
    echo "All tests passed."
else
    eval "$failFormat"
    echo "One or more tests failed."
fi

eval "$normalFormat"

echo
exit $returnStatus