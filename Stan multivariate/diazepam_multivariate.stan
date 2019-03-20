functions{
        //function containing the ODEs
        real [] pbpk(real t,
                    real[] y,
                    real[] theta,
                    real[] rdata,
                    int[] idata) {
                
                real dydt[14] ;
                
                real Q_MU;real Q_AD;real Q_TE;real Q_SK;real Q_HT;real Q_BR;real Q_KI;real Q_RE;
                real Q_ST;real Q_SPL;real Q_LU;real Q_LI;real Q_ART;real Q_VEN;
                
                real V_MU;real V_AD;real V_TE;real V_SK;real V_HT;real V_BR;real V_KI;real V_RE;
                real V_ST;real V_SPL;real V_LU;real V_LI;real V_ART;real V_VEN;
                
                real KP_MU;real KP_AD;real KP_TE;real KP_SK;real KP_HT;real KP_BR;real KP_KI;real KP_RE;
                real KP_ST;real KP_SPL;real KP_LU;real KP_LI;
                
                real CL;real f_UB;real Q_HA;real Q_HP;real Q_H;real T_inf;real dose; real scale_factor; 
                            
                Q_MU = rdata[1];
                Q_AD = rdata[2];
                Q_TE = rdata[3];
                Q_SK = rdata[4];
                Q_HT = rdata[5];
                Q_BR = rdata[6];
                Q_KI = rdata[7];
                Q_RE = rdata[8];
                Q_ST = rdata[9];
                Q_SPL = rdata[10];
                Q_LU = rdata[11];
                Q_LI = rdata[12];
                Q_ART = rdata[11];
                Q_VEN = rdata[11] ;   
                
                V_MU = rdata[13];
                V_AD = rdata[14];
                V_TE = rdata[15];
                V_SK = rdata[16];
                V_HT = rdata[17];
                V_BR = rdata[18];
                V_KI = rdata[19];
                V_RE = rdata[20];
                V_ST = rdata[21];
                V_SPL = rdata[22];
                V_LU = rdata[23];
                V_LI = rdata[24];
                V_ART = rdata[25];
                V_VEN = rdata[26];
                
                
                scale_factor = exp(theta[2]);
                KP_MU = rdata[27]*scale_factor;
                KP_AD = exp(theta[3]);
                KP_TE = rdata[29]*scale_factor;
                KP_SK = rdata[30]*scale_factor;
                KP_HT = rdata[31]*scale_factor;
                KP_BR = rdata[32]*scale_factor;
                KP_KI = rdata[33]*scale_factor;
                KP_RE = rdata[34]*scale_factor;
                KP_ST = rdata[35]*scale_factor;
                KP_SPL = rdata[36]*scale_factor;
                KP_LU = rdata[37]*scale_factor;
                KP_LI = rdata[38]*scale_factor;
        		
              	CL = exp(theta[1]);
              	f_UB = rdata[39];
              	Q_HA = Q_LI;
                Q_HP = Q_SPL + Q_ST;
                Q_H = Q_HA + Q_HP;
               	T_inf = rdata[40];
                dose = rdata[41]; // in mg
                
                
                dydt[1] = Q_MU*(y[13]-y[1]/KP_MU)/V_MU;
                dydt[2] = Q_AD*(y[13]-y[2]/KP_AD)/V_AD;
                dydt[3] = Q_TE*(y[13]-y[3]/KP_TE)/V_TE;
                dydt[4] = Q_SK*(y[13]-y[4]/KP_SK)/V_SK;
                dydt[5] = Q_HT*(y[13]-y[5]/KP_HT)/V_HT;
                dydt[6] = Q_BR*(y[13]-y[6]/KP_BR)/V_BR;
                dydt[7] = Q_KI*(y[13]-y[7]/KP_KI)/V_KI;
                dydt[8] = Q_RE*(y[13]-y[8]/KP_RE)/V_RE;
                dydt[9] = Q_ST*(y[13]-y[9]/KP_ST)/V_ST;
                dydt[10] = Q_SPL*(y[13]-y[10]/KP_SPL)/V_SPL;
                
                dydt[11] = Q_LU*(y[14]-y[11]/KP_LU)/V_LU;
                dydt[12]=(Q_HA*y[13]+Q_ST*y[9]/KP_ST+Q_SPL*y[10]/KP_SPL-(Q_H+CL*f_UB)*y[12]/KP_LI)/V_LI;
                dydt[13] = Q_ART*(y[11]/KP_LU-y[13])/V_ART;
                
                if (t<=T_inf){
                        dydt[14] = (-Q_LU*y[14]+Q_H*y[12]/KP_LI+Q_MU*y[1]/KP_MU+Q_AD*y[2]/KP_AD+
                                Q_TE*y[3]/KP_TE+Q_SK*y[4]/KP_SK+Q_HT*y[5]/KP_HT+
                                Q_BR*y[6]/KP_BR+Q_KI*y[7]/KP_KI+
                                Q_RE*y[8]/KP_RE+dose/(1000*T_inf))/V_VEN  ;//units are in ng/mL
                }
                
                else{
                        dydt[14] = (-Q_LU*y[14]+Q_H*y[12]/KP_LI+Q_MU*y[1]/KP_MU+Q_AD*y[2]/KP_AD+
                                Q_SK*y[4]/KP_SK+Q_TE*y[3]/KP_TE+Q_HT*y[5]/KP_HT+
                                Q_BR*y[6]/KP_BR+Q_KI*y[7]/KP_KI+
                                Q_RE*y[8]/KP_RE)/V_VEN  ;
                }
             
                        return dydt;       
        } 
        
        

}
//////////////////////////////////////////////////////////////////////////
        
data{
                
        int<lower=0> N_subj;           // Number of individuals
        int<lower=0> N_param;          // Number of parameters
        int<lower=0> N_compart;        // Number of compartments
        int  N_obs;                    // Total number of observations
        real  time[N_obs];
        real  con[N_obs];
        int   samp[N_subj];            // Number of samples of each individual
        real y0[N_compart];            // Initial concentration in compartments
        real t_init;                  // Initial time
        real eta_tr[N_param];         //prior parameter means
        real eta_tr_std[N_param];     //prior parameter standard deviatioin
        real  params[41,N_subj];      // Matrix containing the individual parameters
        real R;                       
        real rel_tol;                 // relative tolerance for solver
        real abs_tol;                 // absolute tolerance for solver
        real max_num_steps;           // maximum number of steps for solver
        real a;                       // lkj_corr parameter
 
}

////////////////////////////////////////////////////////////////////////////
        
transformed data {
                
        int idata[0];
        vector[N_param]  eta_std ;              // Transformation of eta_tr in log-space
        vector[N_param]  eta ;                  // Transformation of eta_tr_std in log-space
        cov_matrix [N_param] H;                //covariance matrix
   
        for (i in 1:N_param){
                eta_std[i]= sqrt(log(((eta_tr_std[i]^2)/(eta_tr[i])^2)+1));
                eta[i]=log(((eta_tr[i])^2)/sqrt((eta_tr_std[i]^2)+(eta_tr[i])^2));
        }
                
       for (i in 1:N_param){
                for (j in 1:N_param){
                                
                        H[i,j]=0;
                                
                }
        }

        H[1,1] = eta_std[1]^2;
        H[2,2] = eta_std[2]^2;
        H[3,3] = eta_std[3]^2;
                
}
//////////////////////////////////////////////////////////////////
        
parameters{
 
        real<lower=0>  sigma;             
        vector[N_param] mu;               
        corr_matrix[N_param] C;
        vector<lower=0>[N_param] s; // scales
        vector [N_param] theta_tr[N_subj];
                
}
////////////////////////////////////////////////////
transformed parameters{
        
     
}
////////////////////////////////////////////////////////////////////
        
model{

real y_hat[16,14];
matrix[N_param,N_param] Omega;
int pos;
pos = 1;

//priors
 sigma ~ normal(0,1);
 mu ~ multi_normal(eta,H);
 C ~ lkj_corr(a); 
 s ~ normal(0,1);
 Omega = quad_form_diag(C, s);

 
 //likelihood~  
 
for (j in 1:N_subj){

        theta_tr[j,:] ~ multi_normal(mu,Omega) ;
       
       y_hat[1:samp[j],:] = integrate_ode_bdf(pbpk,y0,t_init,segment(time, pos, samp[j]),
                                                 to_array_1d(theta_tr[j,:]),params[:,j],idata,
                                                 rel_tol, abs_tol,max_num_steps);

       log(segment(con, pos, samp[j])) ~ normal(log( to_vector(y_hat[1:samp[j],14])/R),sigma);
       pos = pos + samp[j];

}

}


generated quantities{

  matrix[N_param,N_param] Omega;

         Omega = quad_form_diag(C, s);
}
