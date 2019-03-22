library(rstan)
library(openxlsx)



rstan_options(auto_write = TRUE)
options(mc.cores = parallel::detectCores())
############################################
#the order of compartments is as follows:
#[1]= MU
#[2]= AD
#[3]= TE
#[4]= SK
#[5]= HT
#[6]= BR
#[7]= KI 
#[8]= RE
#[9]= ST
#[10]= SPL 
#[11]= LU
#[12]= LI
#[13]= ART
#[14]= VEN

########################################################################
# Function that calculates 
predictor<-function(w,gender){
  # Computes the organ weights and regional blood flows of a patient given her/his weight and gender.
  #
  # Args:
  #   w: Weight of the individual in kg.
  #   gender: 0 for males, 1 for females.
  #
  # Returns:
  #   A vector containing the organ flows (12) followed by the organ volumes (14).
        
        k1<-c(9.61e-02,-4.88e-06,3.05e-10,-3.62e-15,1.22e-20,0,0.17)
        k2<-c(3.95e-02,1.59e-05,-6.99e-10,1.09e-14,-5.26e-20,0,0.05)
        k3<-c(1.67e-04,6.2e-10,-6.54e-13,2.48e-17,-2.85e-22,1.03e-27,0.001)
        k4<-c(1.07e-01,-3.26e-06,6.11e-11,-5.43e-16,1.83e-21,0,0.05)
        k5<-c(8.53e-03,-4.07e-07,1.4e-11,-1.9e-16,1.05e-21,-1.94e-27,0.04)
        k6<-c(1.19e-01,-3.51e-06,4.28e-11,-1.82e-16,0,0,0.12)
        k7<-c(7.31e-03,-8.29e-08,5.71e-13,0,0,0,0.19)
        k8<-rep(0,6)
        k9<-c(1.88e-03,8.76e-08,-2.52e-12,1.86e-17,0,0,0.01)
        k10<-c(1.74e-02,-5.3e-07,1.18e-11,-6.74e-17,0,0,0.14)
        k11<-c(1.67e-02,-9.96e-08,-1.09e-13,1.13e-17,0,0,1)
        k12<-c(3.49e-02,-3.23e-07,2.13e-12,0,0,0,0.065)
        k13<-c(3.66e-02,-3.44e-07,5.00e-12, -2.59e-17,0.0,0.0)
        k14<-c(5.49e-02,-5.15e-07, 7.50e-12,-3.87e-17,0.0,0.0)
        
        k1_W<-c(1.17e-01,-3.59e-06,3.19e-10,-3.55e-15,-7.58e-22,0.0)
        k2_W<-c(5.91e-02,1.20e-05,-5.80e-10,1.12e-14,-6.36e-20,0.0)
        k3_W<-c(1.94e-04,-8.32e-09,3.15e-13,0.0,0.0,0.0)
        k4_W<-c(9.54e-02,-1.7e-06,-1.64e-13,2.64e-16,-1.49e-21,0.0)
        k5_W<-c(5.72e-03,-1.02e-07,2.53e-12,-2.71e-17,9.29e-23,0.0)
        k6_W<-c(1.12e-01,-3.33e-06,4.04e-11,-1.70e-16,0.0,0.0)
        k7_W<-c(8.04e-03,-1.38e-07,2.19e-12,-1.34e-17,0.0,0.0)
        k8_W<-rep(0,6)
        k9_W<-c(1.88e-03,8.76e-08,-2.52e-12,1.86e-17,0.0,0.0)
        k10_W<-c(1.89e-02,-6.62e-07,1.56e-11,-9.87e-17,0.0,0.0)
        k11_W<-c(1.74e-02,-7.14e-08,-6.78e-14,0.0,0.0,0.0)
        k12_W<-c(3.59e-02,-4.76e-07,8.50e-12,-5.45e-17,0.0,0.0)
        k13_W<-c(3.66e-02,-3.44e-07,5.00e-12, -2.59e-17,0.0,0.0)
        k14_W<-c(5.49e-02,-5.15e-07, 7.50e-12,-3.87e-17,0.0,0.0)
        
        density <- rep(1,14)
        flow_frac<-c(0.17,0.05,0.005,0.05,0.04,0.12,0.19,0,0.01,0.14,1,0.065)
        flow_frac_w<-c(0.17,0.05,0.002,0.05,0.04,0.12,0.19,0,0.01,0.14,1,0.065)
        
        
        const<-list(k1,k2,k3,k4,k5,k6,k7,k8,k9,k10,k11,k12,k13,k14)
        const_W<-list(k1_W,k2_W,k3_W,k4_W,k5_W,k6_W,k7_W,k8_W,k9_W,k10_W,k11_W,k12_W,k13_W,k14_W)
        vol<-rep(0,14)
        flow<-rep(0,12)
        TF<-(187*(w)^0.81)*60/1000 #Total flow
        weight <- w
        
        if (gender==0){
                if (w>75){
                        w<-75*1000
                }
                else{
                        w<-w*1000
                }
                co<-const
                for (i in 1:14){
                        
                        vol[i]<-(co[[i]][1]+co[[i]][2]*w+co[[i]][3]*w^2+co[[i]][4]*w^3+co[[i]][5]*w^4+co[[i]][6]*w^5)
                        vol[i]<-vol[i]*weight/density[i]
                }
        }
        
        else if (gender==1){
                if (w>65){
                        w<-65*1000
                }
                else{
                        w<-w*1000
                }
                co<-const_W
                for (i in 1:14){
                        
                        vol[i]<-(co[[i]][1]+co[[i]][2]*w+co[[i]][3]*w^2+co[[i]][4]*w^3+co[[i]][5]*w^4+co[[i]][6]*w^5)
                        vol[i]<-vol[i]*weight/density[i]
                }
        }
        
        
        
        for (i in 1:12){
          if (gender==0){
            flow[i]<-TF*flow_frac[i]
          }
          else{
            flow[i]<-TF*flow_frac_w[i]
          }
        }
        
        flow[8]<-TF-sum(flow)+TF
        vol[8]<-weight-sum(vol)
        combine<-c(flow,vol)
        
        return(combine)
        
}
###############################################################################################
Kp <- c(0.56, 3.34, 0.76, 0.46, 0.86, 0.32, 0.73, 2.2, 0.75, 0.53, 0.71, 1.35) #list of blood to tissue partition coefficients
T_inf <- (1/60)/2 #infusion time
FUB<-0.015/0.65

#load data
diaz_data <- read.xlsx("data.xlsx", colNames = TRUE,rowNames = TRUE)
n_physio <- 3 #physiological characteristics: age, gender, weight
concen_missing <- as.matrix(diaz_data[2:(dim(diaz_data)[1]-n_physio),])#matrix of concentration-time profiles with missing values
time <-  c(5/60, 0.25, 0.5, 0.75, 1.0, 1.5, 2.0, 3.0, 4.0, 6.0, 8.0, 10.0, 12.0, 24.0, 30.0, 36.0, 48.0, 72.0)

#create an array to store the number of samples of each patient
samp <- apply(concen_missing, 2, function(x) length(na.omit(x)))
#collapse concentration matrix to a vector
concen <- as.vector((concen_missing))

# Create the corresponding time vector and concentration vector and remove missing values
time_vec <- list()
concen <- list()
for (i in 1:dim(diaz_data)[2]){
  time_vec[[i]] <- time[-which(is.na(concen_missing[,i]))]
  concen[[i]] <- concen_missing[-which(is.na(concen_missing[,i])),i]
}
time_vec <- as.vector(unlist(time_vec))
concen <- as.vector(unlist(concen))


gender <- array(unlist(diaz_data[22,]))
weight <- array(unlist(diaz_data[21,]))

# weight adjusted dose with min dose 5 mg and max 10 mg (produced values in ng)
dose <- 5e+06 + (10-5)*(weight-min(weight)) /(max(weight)-min(weight))*1e06

#create a matrix containing the parameters of all patients
params <- matrix(rep(0, 41*dim(diaz_data)[2]), ncol=23)
for (i in 1:dim(diaz_data)[2]){
  params[,i] <- c(predictor(weight[i],gender[i]), Kp, FUB, T_inf, dose[i])
}

#############################################################################################

Diazepam_dat<-list(
                   eta_tr = c(70.8,1,3.34), #CL, fKp, kp_AD
                   eta_tr_std = c(62.5,1,0.44), 
                   R = 0.65,
                   N_compart = 14.0, #Number of compartments
                   N_subj = 23,		 #Number of individuals
                   N_param = 3.0,    #Number of parameters(per individual)
                   params = params,
                   time = time_vec,
                   con = concen,
                   samp = samp, 
                   N_obs = length(concen), #Total number of observations
                   t_init = 0,             
                   y0 = rep(0,14),
                   rel_tol = 1e-04, 
                   abs_tol = 1e-02,
                   max_num_steps = 1e05,
                   a=15
                 
)

tic = proc.time()

fit <- stan(file = 'multivar2.stan', data = Diazepam_dat, 
            iter = 5400, warmup=400, chains=4)
options(max.print=5.5E5) 
print(fit)

#Check diagnostic tools
check_hmc_diagnostics(fit)

#Use shinystan for inference
library(shinystan)
launch_shinystan(fit)
print(fit)



