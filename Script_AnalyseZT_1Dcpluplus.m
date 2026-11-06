%************************************************************************************************************************************************************
% Compile:
%     g++ -g -O3 -std=c++11 main_Mangoni1D.cpp -o mangoni.o
% 
%initial_condition_default  ---- "On"/"Off"          ---- If initial condition are defaulted (On) or they need an input file (initial_conditions.csv)
%version_default            ---- int (1, 2)          ---- Different sets of initial conditions. Default: 2.
% BCL                        ---- double (ms)         ---- Basic Cycle Length
% Ncells                     ---- int                 ---- Number of myocytes
% Phi_type/Macrophage_type   ---- int (0, 1, 2, 12)   ---- Type of macrophage (different currents)
% Macrophage_coupling        ---- "On"/"Off"          ---- Activate/deactivate coupling with macrophage
% Total_time                 ---- double (ms)         ---- Total simulation time
% Ncells_stim                ---- int                 ---- Number of stimulated myocytes (the Ncells_stim first)
% dcells_Macrophage          ---- int                 ---- Macrophage coupling every dcells_Macrophage cells
% Ggap_scale                 ---- float               ---- Scales the strength of adjacent myocytes coupling
% Ggapm_scale                ---- float               ---- Scales the strength of coupling with macrophage
% Reference                  ---- const char          ---- Folder to store output in
% N_Phi			   ---- int 		    ---- Number of Macrophages coupled to myocyte
% Time_Application_Circ     ---- double (ms)         ---- Time to start to Apply increase in Ca1.2 and Cav1.3

% Increment_Cav                    ---- double dimensionless
% Increment_Kr                       ---- double dimensionless
% 
% Example:
%  

% AVNmangoni_Circ.exe Ncells 100 BCL 171.4286 Ggap_scale 3000 Ncells_stim 5 Total_time 5000 Macrophage_coupling Off Time_Application_Circ 0 Increment_Cav 0.85 
% Increment_Kr 4.5 Increment_KAch 1 Reference Test_ZT0_Cav0_85IKr4_5IKACh1_04082026Circ
%*****************************************************************************************************************************************************************************
%%
% clc
% clear
% analyse=0;
% 
%  Nbrecell=100;
% Ncells=Nbrecell;
% Macrophage_coupling='Off';
% 
%  Total_time=5000;
%  dcells_Macrophage=2;
%  Ggap_scale=3000;
%  Ggapm_scale=7;
%  Ncells_stim=5;
% BPM=350;
% BCL=60*1e3/BPM;
%BCL=133.33;
%BPM=BCL/60*1e3;
% Time_Application_Circ=0;
%  factor_Cav=1.2;
% 
% Reference ='Test_15042026_Circ_Increment_Cav';
% %mkdir(Reference)
% %dir_root=pwd;
% %Chemin=[dir_root,'\',Reference,'\'];
% commande_Simul=['AVNmangoni_Circ.exe ',' BCL ' ,num2str(BCL), ' Ncells ',num2str(Ncells),...
%     ' Ggap_scale ' ,num2str(Ggap_scale)  ,' Ncells_stim ',num2str(Ncells_stim),...
%     ' Total_time ' ,num2str(Total_time),' Macrophage_coupling ' ,Macrophage_coupling,...
%        ' Time_Application_Circ ',num2str(Time_Application_Circ),' Increment_Cav ',num2str(factor_Cav),' Reference ', Reference];
% 
% 
% 
% tic
% [status,~] = system(commande_Simul);

%system( ['powershell -command',[" cd e:\Analyse_Cardiac_AVN_Cplusplus_circ_13082026;.\Simul.bat"' );

% save([Chemin,'param_data','.mat'],'-mat','-v7.3')
% toc
%**************************************************************************************************************************************

%*******************************************************************************************************************************************

%%
% 
% fid = fopen('commande_Simul.bat','w');
% fprintf(fid,'%s\n',commande_Simul);
%  fclose(fid);
% system('commande_Simul.bat')

%%
clc
clear
Nbrecell=100;
ZT=zeros(4,3);
ZT(1,:)=[0.3;4.5;1];
ZT(2,:)=[0.2;4;1];
ZT(3,:)=[0.35;1.8;1];
ZT(4,:)=[1;4.5;1];
incCav=0.85;
incKr=1.2;
incKACh=900;

%Name_Analyse='ICav';
%Name_Analyse='Ikr';
Name_Analyse=['ZT_0','ICav',num2str(incCav),'IKr',num2str(incKr),'IKACh',num2str(incKACh)];
Name_Analyse1=['ZT_0','ICav',num2str(incCav),'IKr',num2str(incKr),'IKACh',num2str(incKACh)];
%Name_Analyse='IKACh';
deltax=65*1e-3;%mm
flag_save=0;
TotalTime=5000;
t_application=0; %msec

dir_root=  uigetdir('E:');
if dir_root==0
    return
else
Chemin=[dir_root,'\'];
end
%Igap_AV1=zeros(Total_time,Ncells);
%Igap_AV=zeros(Total_time,Ncells);
%Igap_Phi=zeros(Total_time,Ncells);
f = waitbar(0,'Please wait...');
for i=1:Nbrecell 
    file=[Chemin,'Output_',num2str(i-1),'.txt'];
    if i==1
        data=importdata(file);
        Time        = zeros(size(data,1),Nbrecell);
        Vm          = zeros(size(data,1),Nbrecell);
        IKr           = zeros(size(data,1),Nbrecell);
        ICav_1_3 = zeros(size(data,1),Nbrecell);
        ICav_1_2 = zeros(size(data,1),Nbrecell);
        IKACh      = zeros(size(data,1),Nbrecell);
        ICaL_Tot  = zeros(size(data,1),Nbrecell);
        Time(:,i)         = data(:,1);
        Vm(:,i)           = data(:,2);
        IKr(:,i)            = data(:,50);
        ICav_1_3(:,i) = data(:,47);
        ICav_1_2(:,i) = data(:,46);
        ICaL_Tot(:,i)=ICav_1_2(:,i)+ICav_1_3(:,i);
        IKACh(:,i)       = data(:,62);
    else
        data=importdata(file);
        Time(:,i)=data(:,1);
        Vm(:,i)=data(:,2);
        IKr(:,i)=data(:,50);
        ICav_1_3(:,i)=data(:,47);
        ICav_1_2(:,i)=data(:,46);
        ICaL_Tot(:,i)=ICav_1_2(:,i)+ICav_1_3(:,i);
      
        IKACh(:,i)       = data(:,62);
    end
   


waitbar(round(i/Nbrecell),f,sprintf('%3d',i));

end
close(f)
Ko=5.4;
Cm=22;
gKAChCtrl=0.0000001*Ko^0.41;
gKACh=incKACh*gKAChCtrl;
gKrCtrl=(0.3*0.005)/Cm;
gKr=incKr*gKrCtrl;
GCaL=0.07/Cm;

GCav1_2=incCav*GCaL;
GCav1_3=incCav*1.95*GCaL;

t=Time(:,1);


%if analyse==1

    episode=1;
figure(episode)
 
subplot(2,2,1)

imagesc(t,(1:Nbrecell).*deltax,Vm')
xlabel('time msec');ylabel('distance mm')
subtitle(['Vm mV',num2str(incCav),'IKr',num2str(incKr),'IKACh',num2str(incKACh)])
colorbar
subplot(2,2,2)

imagesc(t,(1:Nbrecell).*deltax, ICaL_Tot')
xlabel('time msec');ylabel('distance mm')
title('ICaL Total pA/pF')
colorbar

subplot(2,2,3)

imagesc(t,(1:Nbrecell).*deltax, IKr')
xlabel('time msec');ylabel('distance cm')
subtitle('IKr Total pA/pF')
colorbar
subplot(2,2,4)

imagesc(t,(1:Nbrecell).*deltax, IKACh')
xlabel('time msec');ylabel('distance cm')
title('IKACh Total pA/pF')
colorbar


saveas(gcf,[Chemin,'Synthesis_',Name_Analyse,'.jpg'],'jpeg')

%******************************************

for panel=1:10:100
 figure(episode+ panel)
k=1;
for cell=panel:9+panel
subplot(10,1,k)
 hold on  
plot(t,Vm(:,cell))
yyaxis  right
% plot(t,Igap_Phi(:,cell))

switch Name_Analyse

    case 'Ikr'
    plot(t,IKr(:,cell))
    case 'ICav'
    plot(t,ICav_1_2(:,cell))
    plot(t,ICav_1_3(:,cell))
    plot(t, ICaL_Tot(:,cell))
    case 'IKACh'
    plot(t,IKACh(:,cell))
    case Name_Analyse1
      plot(t,IKr(:,cell))
      plot(t,ICav_1_2(:,cell))
      plot(t,ICav_1_3(:,cell))
        plot(t, ICaL_Tot(:,cell))
      plot(t,IKACh(:,cell))
end

hold off 
% %plot([t(1) t(end)],[0 0])
 yyaxis left
ylabel(['Cell ',num2str(cell)])

k=k+1;
end
 saveas(gcf,[Chemin,'AP time course_',Name_Analyse,num2str(incCav),'_',num2str(panel),'.jpg'],'jpeg')
end
%*****************************************************************
figure('Name','Population Cells')
k=1;
hold on
for cell=Nbrecell:-1:1 
plot(t,Vm(:,cell)+k)
k=k+100;
end
hold off
saveas(gcf,[Chemin,'Population Cells_',Name_Analyse,num2str(incCav),'_',num2str(panel),'.jpg'],'jpeg')
%***************************************************************
 ICaL_min=min(min(ICaL_Tot(t>100,:)));
 ICaL_max=max(max(ICaL_Tot(t>100,:)));
 

 ICav_1_3_min=min(min(ICav_1_3(t>100,:)));
 ICav_1_3_max=max(max(ICav_1_3(t>100,:)));

 ICav_1_2_min=min(min(ICav_1_2(t>100,:)));
  ICav_1_2_max=max(max(ICav_1_2(t>100,:)));


 IKr_min=min(min(IKr(t>100,:)));
 IKr_max=max(max(IKr(t>100,:)));


 IKACh_min=min(min(IKACh(t>100,:)));
 IKACh_max=max(max(IKACh(t>100,:)));

%*********************************************************************
%*********************************************************************
%
%***********************************************************************

%***************************************************************************     
% dir_root=  uigetdir('E:');
% Chemin=[dir_root,'\'];


dx=0.065028; %mm
%Nbrecell=Ncells;
%indextime=find(t<t_application,1,"last");
BpmTable=zeros(Nbrecell,2);
for cell=1:Nbrecell
 Tf=islocalmax(Vm(:,cell),'minProminence',5,'MinSeparation',100,'SamplePoints',t);
Tmdp=islocalmin(Vm(:,cell),'minProminence',5,'MinSeparation',100,'SamplePoints',t);
Events{cell}=Tf;
EventsMDP{cell}=Tmdp;




Nbre1=sum(Tf);

BpmTable(cell,1)=Nbre1;
BpmTable(cell,2)=60*Nbre1/(TotalTime*1e-3);


end


%********************************************************************************
% recherche du seuil et 90% repolarisation
%**********************************************************************************

clc
dt=mean(diff(t));
dvdt=Vm;
for cell=1:Nbrecell
    
dvdt(:,cell)=[diff(Vm(:,cell));0];

 Tf=islocalmax(Vm(:,cell),'minProminence',5,'MinSeparation',100,'SamplePoints',t);
Tmdp=islocalmin(Vm(:,cell),'minProminence',5,'MinSeparation',100,'SamplePoints',t);
%Tdvdt=islocalmax(dvdt(:,cell),'minProminence',0.5,'MinSeparation',150,'SamplePoints',t);
Events{cell}=Tf;
EventsMDP{cell}=Tmdp;
   
Tmax=Events{cell};
Tmdp=EventsMDP{cell};

indexTmax=find(Tmax);
indexTmdp=find(Tmdp);

tfin=20;

Fenetre_detection=round(tfin/dt);
TSeuil=false(size(Vm,1),1);
T90=false(size(Vm,1),1);
for i=1:length(indexTmax)-1
Amp=Vm(indexTmax(i),cell);
  [s, ~]=Recher_Start_Stop(dvdt(:,cell),indexTmax(i),2,Fenetre_detection);
  if s==0
      s=1;
  end


 TSeuil(s)=true;
 Inmdp=find(indexTmdp>indexTmax(i),1,'first');
 
 Amp90=Amp -(Amp-Vm(indexTmdp(Inmdp),cell))*0.90;
index90=indexTmax(i)+find(Vm(indexTmax(i):indexTmdp(Inmdp),cell)>Amp90,1,'last');
T90(index90)=true;

end

T90repol{cell}=T90;
SeuilPa{cell}=TSeuil;



end

%***************************************************************************
distance_strand=(1:Nbrecell).*deltax;
figure('Name',['Map_PA Parameters ',Name_Analyse,' Modulation' ]);
imagesc(t,distance_strand,Vm')
hold on
for cell=1:Nbrecell
    Tpa=Events{cell};
    Tmdp=EventsMDP{cell};
    T90=T90repol{cell};
    TSeuil=SeuilPa{cell};
    %*******************************
    indextimepa=find(Tpa);
    indextimeMDP=find(Tmdp);
    indextimeT90=find(T90);
    indextimeSeuil=find(TSeuil);
    %**********************************
    pamax=indextimepa;
    pamax(:)=distance_strand(cell);
    pamdp=indextimeMDP;
    pamdp(:)=distance_strand(cell);
    paseuil=indextimeSeuil;
    paseuil(:)=distance_strand(cell);
    paT90=indextimeT90;
    paT90(:)=distance_strand(cell);

    plot(t(indextimepa),pamax,'*r','MarkerSize',10)
    plot(t(indextimeT90),paT90,'og','MarkerSize',10)
    plot(t(indextimeSeuil),paseuil,'+r','MarkerSize',10)
    plot(t(indextimeMDP),pamdp,'>c','MarkerSize',10)

    nbre=length(indextimeT90);

    APD90{cell}=t(indextimeT90)-t(indextimeSeuil(1:nbre));

end
hold off
savefig(gcf,[Chemin,'Map_PA Parameters_',Name_Analyse,num2str(incCav),'.fig']);

figure('Name',['APD90 PA Parameters ',Name_Analyse,' Modulation' ]);
hold on
for cell=1:Nbrecell
APD_S=APD90{cell};
plot(APD_S)
end
hold off
savefig(gcf,[Chemin,'APD90 Distribution_',Name_Analyse,num2str(incCav),'.fig']);

figure('Name',['MDP PA Parameters ',Name_Analyse,' Modulation' ]);
hold on
for cell=1:Nbrecell
Tmdp=EventsMDP{cell};  
indextimeMDP=find(Tmdp);
plot(Vm(indextimeMDP,cell))
MDP{cell}=Vm(indextimeMDP,cell);
end
hold off
%****************************************************************

 for i=1:Nbrecell
    nc=i;

    %figure(nc)


    Tpa=Events{nc};
    Tmdp=EventsMDP{nc};
    T90=T90repol{nc};
    TSeuil=SeuilPa{nc};
    %*******************************
    indextimepa=find(Tpa);
    indextimeMDP=find(Tmdp);
    indextimeT90=find(T90);
    indextimeSeuil=find(TSeuil);

    % plot(t,Vm(:,nc))
    % hold on
    % plot(t(indextimepa),Vm(indextimepa,nc),'*r','MarkerSize',10)
    % plot(t(indextimeT90),Vm(indextimeT90,nc),'og','MarkerSize',10)
    % plot(t(indextimeSeuil),Vm(indextimeSeuil,nc),'+r','MarkerSize',10)
    % plot(t(indextimeMDP),Vm(indextimeMDP,nc),'>c','MarkerSize',10)
    % hold off

   Ioff=find(t(indextimeSeuil));

 
 APD90{nc}=t(indextimeT90(Ioff))-t(indextimeSeuil(Ioff));


%tableduree=[t(indextimeSeuil),t(indextimeT90),t(indextimeT90)-t(indextimeSeuil)];
end

   Pool_APD=[];Pool_MDP=[];
   for i=1:Nbrecell
       %
       tmp_APD= APD90{i} ;
       tmp_MDP=MDP{i};
       Pool_APD=[Pool_APD; tmp_APD];
       Pool_MDP=[Pool_MDP;tmp_MDP];
       % %
    

   end
 


%%

%********************************************************************************
% VC measurements

Nc1=10;Nc2=80;
Nb=Nc2-Nc1;

   Tf=Events{Nc1};
   Tl=Events{Nc2};

        indexT1=find(Tf);
        indexT2=find(Tl);
  
        distance=Nb * 65 *1e-3;%mm

        Tf_pamax=t(indexT1).*1e-3; % temps des Pa premiere myo
        Tl_pamax=t(indexT2).*1e-3; % temps des Pa derniere myo
        % if length(Tl_pamax)< length(Tf_pamax)


figure
hold on
plot(t,Vm(:,Nc1),'b')

plot(t,Vm(:,Nc2),'r')
plot(t( Tf),Vm(Tf,Nc1),'db','MarkerSize',10,'MarkerFaceColor','b')
plot(t(Tl),Vm(Tl,Nc2),'sr','MarkerSize',10)
hold off

        
        % end
        k=1;
      for i=1:length(Tf_pamax)-3
       % index_wave= find(Tl_pamax>Tf_pamax(i), 1,'first');
       % if  ~isempty(index_wave)
        %tempsTwdfTwf=[Tf_pamax(i) Tl_pamax(index_wave)];
        debut_wave(k)=Tf_pamax(i) ;
        fin_wave(k)=Tl_pamax(i);
        duree(k)=Tl_pamax(i)-Tf_pamax(i);
      vconduction(k)=distance/  duree(k);

       k=k+1;
        %end
      end
       
        
 
%***********************************************************************************************
        figure('Name',['Conduction Velocity per Max Upstroke',Name_Analyse,' Modulation' ])
      
            plot(debut_wave,vconduction,'or','MarkerSize',5)
  
    
        ylabel('Conduction Velocity (mm/sec)')
        xlabel('Time Beat (sec)')
        title(['Conduction Velocity (mm/sec)',num2str(incCav),'IKr',num2str(incKr),'IKACh',num2str(incKACh)])
        saveas(gcf,[Chemin,'Conduction_Velocity_',Name_Analyse,'.jpg'],'jpeg')
       
        %*****************************************************************************************
       figure('Name','APD90 Distribution')
         histogram(Pool_APD,30)

   
        saveas(gcf,[Chemin,'APD90 Distribution_',Name_Analyse,'.jpg'],'jpeg')

        figure('Name','MDP Distribution')
         histogram(Pool_MDP,30)

   
        saveas(gcf,[Chemin,'MDP Distribution_',Name_Analyse,'.jpg'],'jpeg')



     %***********************************************************************************************
         Result_VC = table(debut_wave', fin_wave',duree',vconduction');
         Result_VC .Properties.VariableNames=["Beat Time debut","Beat Time fin","duree", "VC"];
        
        writetable( Result_VC,[Chemin,'Conduction Velocity_',Name_Analyse,'_','.csv'],'Delimiter','tab');
        
      
       
       

          Result_APD = table(Pool_APD);

          Result_MDP=table(Pool_MDP);

          Result_Current=table( ICaL_min,ICaL_max,ICav_1_3_min,ICav_1_3_max,ICav_1_2_min,ICav_1_2_max,...
                                       IKr_min, IKr_max,IKACh_min, IKACh_max);

        Result_Conductance=table( GCav1_2,GCav1_3, gKr,gKACh);

        Result_Frequency=table(BpmTable(:,1),BpmTable(:,2));

         Result_APD .Properties.VariableNames="APD90";

         Result_MDP.Properties.VariableNames="MDP";

        Result_Conductance.Properties.VariableNames=["GCav1_2","GCav1_3","gKr","gKACh"];

       Result_Current.Properties.VariableNames=["min ICaL","max ICaL",...
       "min ICav_1_3","max ICav_1_3","min ICav_1_2","max ICav_1_2",...
       "min IKrl","maxIKr","min IKACh","max IKACh"];

       Result_Frequency.Properties.VariableNames=["Spike Number","BPM (beat/min)"];

      writetable( Result_APD,[Chemin,'APD90_',Name_Analyse,'_','.csv'],'Delimiter','tab');
      writetable( Result_MDP,[Chemin,'MDP_',Name_Analyse,'_','.csv'],'Delimiter','tab');
     writetable( Result_Current,[Chemin,'Currents_',Name_Analyse,'.csv'],'Delimiter','tab');
     writetable( Result_Conductance,[Chemin,'Conductance_',Name_Analyse,'.csv'],'Delimiter','tab');
      writetable( Result_Frequency,[Chemin,'Frequency_',Name_Analyse,'.csv'],'Delimiter','tab');


        %****************************************************************************************************
 save([Chemin,['Synthese_',Name_Analyse],'.mat'],'-mat');
%******************************************************************************************
% Affiche Resultat
%******************************************************************************************
% figure(episode+Nbrecell*8)
% subplot(1,2,1)
% histogram(Pool_APD90off,30) 
% hold on
% histogram(Pool_APD90on,30) 
% subplot(1,2,2)
% histogram(vconduction1,30) 
% hold on
% histogram(vconduction2,30) 
%end

