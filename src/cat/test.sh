#!/bin/bash


echo "None flags --------------------------------------------------------"
./s21_cat cat_3.txt > test1.txt
cat cat_3.txt > test2.txt
diff -s test1.txt test2.txt
DIFF_RES="$(diff -s test1.txt test2.txt)"
if [ "$DIFF_RES" == "Files test1.txt and test2.txt are identical" ]
  then
    (( success_count++ ))
      echo "OK"
  else
      (( fail_count++ ))
      echo "FAIL"
fi
rm test1.txt test2.txt

echo "Flag -b --------------------------------------------------------"
./s21_cat -b cat_3.txt> test1.txt
cat -b cat_3.txt > test2.txt
diff -s test1.txt test2.txt
DIFF_RES="$(diff -s test1.txt test2.txt)"
if [ "$DIFF_RES" == "Files test1.txt and test2.txt are identical" ]
  then
    (( success_count++ ))
      echo "OK"
  else
      (( fail_count++ ))
      echo "FAIL"
fi
rm test1.txt test2.txt

echo "Flag -e --------------------------------------------------------"
./s21_cat -e cat_3.txt > test1.txt
cat -e cat_3.txt> test2.txt
diff -s test1.txt test2.txt
DIFF_RES="$(diff -s test1.txt test2.txt)"
if [ "$DIFF_RES" == "Files test1.txt and test2.txt are identical" ]
  then
    (( success_count++ ))
      echo "OK"
  else
      (( fail_count++ ))
      echo "FAIL"
fi
rm test1.txt test2.txt

echo "Flag -n --------------------------------------------------------"
./s21_cat -n cat_3.txt > test1.txt
cat -n cat_3.txt > test2.txt
diff -s test1.txt test2.txt
DIFF_RES="$(diff -s test1.txt test2.txt)"
if [ "$DIFF_RES" == "Files test1.txt and test2.txt are identical" ]
  then
    (( success_count++ ))
      echo "OK"
  else
      (( fail_count++ ))
      echo "FAIL"
fi
rm test1.txt test2.txt

echo "Flag -s --------------------------------------------------------"
./s21_cat -s cat_3.txt > test1.txt
cat -s cat_3.txt> test2.txt
diff -s test1.txt test2.txt
DIFF_RES="$(diff -s test1.txt test2.txt)"
if [ "$DIFF_RES" == "Files test1.txt and test2.txt are identical" ]
  then
    (( success_count++ ))
      echo "OK"
  else
      (( fail_count++ ))
      echo "FAIL"
fi
rm test1.txt test2.txt

echo "Flag -t --------------------------------------------------------"
./s21_cat -t cat_3.txt > test1.txt
cat -t cat_3.txt> test2.txt
diff -s test1.txt test2.txt
DIFF_RES="$(diff -s test1.txt test2.txt)"
if [ "$DIFF_RES" == "Files test1.txt and test2.txt are identical" ]
  then
    (( success_count++ ))
      echo "OK"
  else
      (( fail_count++ ))
      echo "FAIL"
fi
rm test1.txt test2.txt

echo "SUCCESS: $success_count"
echo "FAIL: $fail_count"
