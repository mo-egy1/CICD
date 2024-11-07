#!/bin/bash
# sudo su gitlab-runner
# ssh-keygen -t rsa -b 2048
# ssh-copy-id selysecr@10.0.2.15
# ssh selysecr@10.0.2.15
scp src/cat/s21_cat selysecr@10.0.2.15:~/
scp src/grep/s21_grep selysecr@10.0.2.15:~/
ssh selysecr@10.0.2.15 "echo "qwe" | sudo -S mv s21_cat s21_grep /usr/local/bin"
