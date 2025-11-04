# Data Analysis: Life Expectancy and Education

<div align="center">  
  <img src="data%20analysis/images/jupyternotebook.png" alt="jupyter notebook" width="470" height="247">
</div>

### Author: Jenny Yu
*July 2023*

---

## Table of Contents
- [Process](#process)
- [Introduction](#introduction)
- [Data Exploration](#data-exploration)
- [Data Preprocessing](#data-preprocessing)
- [Feature and Model Selection](#feature-and-model-selection)
- [Model Training and Evaluation](#model-training-and-validation)
- [Results and Conclusions](#results-and-conclusions)
- [Aknowledgements](#aknowledgements)

---

## Process
[Back to top](#table-of-contents)

1. Setup
2. Data Preprocessing
3. Data Visulaization
4. Evaluation Metrics
5. Model Trainings (Linear Regression and Generalized Linear Model)
6. Results
7. Ethics

---

## Introduction
[Back to top](#table-of-contents)

### Objective

The goal of this project is to explore the **relationship between education and life expectancy** across different countries.
Specifically, I investigated whether the average number of years spent in school correlates with a country's life expectancy.

Understanding these relationships can reveal how education impacts public health outcomes, helping policymakers and researchers identify what factors contribute to longer, healthier lives around the world.

<img src="data%20analysis/images/python.webp" alt="python logo" width="470" height="247">

### Dataset

The dataset was found on [Kaggle](https://www.kaggle.com/datasets/amirhosseinmirzaie/countries-life-expectancy) and details for the columns can also be found on the site. It contains country-level statistics that may influence life expectancy such as BMI, GDP, vaccination rates, infant deaths, and more.

For this project, the main focus was on the “Schooling” column and its relationship with “Life Expectancy” from the years 2000–2015.

---

## Data Exploration
[Back to top](#table-of-contents)

During the exploratory analysis:
  - Schooling showed the strongest correlation with life expectancy among all features.
  - Both schooling and life expectancy have shown an upward trend globally from 2000 to 2015.

Key visualizations:
  - Correlation heatmaps and scatter plots showed clear positive relationships.
  - Linear trends confirmed schooling as a strong predictor of life expectancy.

<img src="C--%20Compiler/images/C.png" alt="C logo" width="250" height="276">

---

## Data Preprocessing
[Back to top](#table-of-contents)

To ensure data quality and consistency, the following preprocessing steps were performed:
  - Handled missing values by replacing NaNs with column averages.
  - Removed outliers by capping data within reasonable bounds.
  - Checked for negative values and duplicate rows.

---

## Feature and Model Selection
[Back to top](#table-of-contents)

To optimize model performance, relevant features were selected and engineered:
- Key evaluation metrics included:
  - Mean Squared Error (MSE)
  - Deviance
- Focused on variables most closely associated with life expectancy.

Two models were chosen for comparison:
1. Linear Regression: Ideal for identifying the linear relationship between schooling and life expectancy.
2. Generalized Linear Model (GLM): Useful for understanding non-linear relationships and evaluating model deviance.

Both models were selected for their interpretability and ability to show relationships between independent and dependent variables.

---

## Model Training and Evaluation
[Back to top](#table-of-contents)

The dataset was split into:
  - Training set: 80%
  - Testing set: 10%
  - Validation set: 10%

### Model 1: Linear Regression
- Trained on the processed dataset.
- Evaluated using **Mean Squared Error** to determine the best-fit line.
- Produced a strong positive correlation between years in school and life expectancy.
<div align="center">  
  <img src="C--%20Compiler/images/C.png" alt="C logo" width="250" height="276">
</div>

### Model 2: Generalized Linear Model (GLM)
- Used a **Gaussian process** to assess correlations between variables.
- Evaluated model fit using Deviance.
- The varience was high so the relationship between the variables was low and Linear Regression showed better results.

---

## Results and Conclusions
[Back to top](#table-of-contents)

### Results:

- Linear Regression performed better than GLM, showing a strong positive correlation between schooling and life expectancy.
- The results indicate that increased years of education are associated with higher life expectancy.
- This suggests that improving access to education can contribute to longer and healthier lives globally.

In summary:
- The more years of schooling a population has, the higher their average life expectancy tends to be.

### Future Recommendations:

- Incorporate more recent data from additional countries to make findings more current.
- Experiment with other machine learning models to capture more complex relationships.
- Explore alternative methods for handling NaN values and outliers for improved data representation.
- Conduct deeper research into why education influences life expectancy (e.g., income, healthcare access, literacy rates).

### Limitations:
While this analysis revealed a strong correlation, it does not establish causation.
  - The dataset may not fully represent all countries or more recent global conditions.
  - Other unexamined factors (e.g., healthcare spending, social inequality) could also influence life expectancy.
  - A broader dataset and additional models could strengthen and validate the conclusions.

This project provides an initial look into how education correlates with life expectancy, highlighting the importance of continued research on this topic.

---

## Aknowledgements
[Back to top](#table-of-contents)

- Thank you AMIRHOSSEIN MIRZAEI for providing the *Countries Life Expectancy* dataset on [Kaggle](https://www.kaggle.com/datasets/amirhosseinmirzaie/countries-life-expectancy)



