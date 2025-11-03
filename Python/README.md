[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/FCyqBoQZ)
# Final-Project

![image](https://github.com/CSC380-SU23-UofArizona/final-project-JennyYu2/assets/89495302/d0b8c456-1cc9-4c20-b091-b3847e523630)

### Outline of the project:
- Exploratory Data Analysis
- Problem 1: Setup
- Problem 2: Improvements
- Problem 3: Data Collection
- Problem 4: Data Preprocessing
- Problem 5: Data Visulaization
- Problem 6: Evaluation Metrics
- Problem 7: Model Training (one)
- Problem 8: Model Training (two)
- Problem 9: Report Results
- Problem 10: Notebook Presentation
- Problem 11: Edit README
- Problem 12: Ethics Question

### Objective:
The goal of this project was to find the correlation between the number of years spent in school and the life expectancy of a country. It's interesting to see the factors that can affect life expectancy and the correlation between the factors and life expectancy. Seeing the relationship between life expectancy and common factors can also tell us what needs to be done for countries that are struggling in maintaining a healthy population. 

### Dataset:
The dataset was found on [Kaggle](https://www.kaggle.com/datasets/amirhosseinmirzaie/countries-life-expectancy) and details for the columns can also be found on the site. The dataset contains information on factors that can affect a country's life expectancy, like BMI, GDP, vaccination percentages, infant deaths, etc. I chose to look at how schooling affected life expectancy.

### Data Exploration and Insights:
- During the data exploration, I observed that schooling had the highest correlation with life expectancy.
- I also saw that schooling and life expectancy have both generally gone up in the different countries from 2000-2015
- ![image](https://github.com/CSC380-SU23-UofArizona/final-project-JennyYu2/assets/89495302/302b80ec-e610-4ce6-96df-4f4c792fcca0)\
- ![image](https://github.com/CSC380-SU23-UofArizona/final-project-JennyYu2/assets/89495302/a404293e-38a8-4155-8e3e-8265414e9b9f)
- ![image](https://github.com/CSC380-SU23-UofArizona/final-project-JennyYu2/assets/89495302/6191181a-9a2c-46cc-8daf-9251a76cf935)

### Data Preprocessing:
- To ensure data quality and suitability for modeling, I performed the following steps:
  - Data cleaning by replacing all NaN values with the average of the column
  - Removing any outliers by capping the data to a certain range
  - Checking for negative values and duplicate rows

### Feature Selecting/Engineering:
- I conducted feature selection/engineering to improve model performance. The selected features were:
    - Mean Squared Error
    - Deviance

### Model Selection:
- After analyzing the different algorithms, I chose Linear Regression and Generalized Linear Model as they are well-suited for this task
- Linear Regression was chosen because it shows the relationship between independent and depenend variables, which is what I was looking to find between schooling and life expectancy.
- Generalized Linear Model was chosen because it also shows the relationship between two variables which is what I was looking to see.

### Model Training and Evaluation:
- The data was split into training and testing sets. I used train(80%), test(10%) and split(10%) to assess the accuracy of the model.
  - Model 1: Used train, test, split and then applited Mean Squared Error to find the line of best fit to asses correlation
  - ![image](https://github.com/CSC380-SU23-UofArizona/final-project-JennyYu2/assets/89495302/f20b1466-fdbd-4f48-9439-1421856ee889)
  - Model 2: Used Gaussian process to find correlation between columns and then used Deviance to look at how well the model fits the data 

### Results and Conclusions:
- Based on the evaluation, Linear Regression was the better model to find a correlation between schooling and life expectancy. It showed a high correlation with the fit of the line while the Deviance value from GLM was poor. But based on the results I can conclude that schooling has a positive impace on life expectancy and the general trend is that the more years of schooling someone has, the higher their life expectancy.
- This means that schooling plays a large part in determining life expectancy and it can be looked at more indepth to help countries increase life expectancies.
- I found that schooling does affect the life expectancy of a country and found the relationship to be generally positive.

### Future Recommendations:
- Using more data from more countries in more recent years can improve this project and make it more applicable to modern day
- Training a different model can also be useful in looking at other correlations in the dataset or for understanding the correlation I looked at
- Handeling of NaN values and outliers can also be changed so the data better represents each country
- Looking more into the reasons why schooling affects life expectancy could be a good follow up project

### Limitations:
While this project showed the correlation between schooling and life expectancy, it doesn't show why there is such a correlation or how the correlation between schooling and life expectancy compares to other factors that might also affect life expectancy. There could also be a better model that shows the results of the project better than I did and there can be better datasets that include a larger range of data than the one I used. It's important to note that this project serves as a glimpse of what can affect a country's life expectancy and it isn't a perfect representation of every country. This project showed a general correlation but it requires further research and analysis to understand the correlation and what it means for a country. 

### Aknowledgements:
- Thank you AMIRHOSSEIN MIRZAEI for providing the Countries Life Expectancy dataset on Kaggle



