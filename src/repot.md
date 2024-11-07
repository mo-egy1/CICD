# Basic CI/CD By selysecr

## Part 1. Setting up the gitlab-runner

* Start `Ubuntu Server 20.04 LTS` virtual machine



  ![Part_1](/src/images/part1/1_1.PNG)


* Download and install `gitlab-runner`  on the virtual machine

  ![Part_1](/src/images/part1/1.PNG)
  
  ![Part_1](/src/images/part1/2.PNG)
  
  ![Part_1](/src/images/part1/3.PNG)
  
  ![Part_1](/src/images/part1/4.PNG)

  ![Part_1](/src/images/part1/5.PNG)

* Run `gitlab-runner` and register it for use in the current project `(DO6_CICD)`



  
  ![Part_1](/src/images/part1/6.PNG)
  
  ![Part_1](/src/images/part1/7.PNG)






## Part 2. Building



* Write a stage for CI to build applications from the C2_SimpleBashUtils project:


  ![Part_2](/src/images/part2/1.png)



  ![Part_2](/src/images/part2/2.png)


## Part 3. Codestyle test


* Write a stage for CI that runs a codestyle script (clang-format):


  ![Part_3](/src/images/part3/1.png)
  

  ![Part_3](/src/images/part3/2.png)





## Part 4. Integration tests


* Write a stage for `CI` that runs your integration tests from the same project:


  ![Part_4](/src/images/part4/1.png)


  ![Part_4](/src/images/part4/2.png)




## Part 5. Deployment stage


  ![Part_5](/src/images/part5/1.png)
  
  
  ![Part_5](/src/images/part5/2.png)
