%%%%%%%%%%%%%%%%%%%%%%%%%%%%做实验测试RANSAC算法%%%%%%%%%%%%%%%%%%%%%%%%%%%%
clc;
clear all;
close all;
datasetx = [1 2 3 4 5 5 7 8 9  9 11 12 13 15 15 16 17 18 19  2 3   4 7  8 9 10 11 12 13 14];    %数据集x轴值
datasety = [1 2 2 4 5 6 7 8 9 10 11 10 14 14 15 17 17 19 19 16 14 18 15 3 4 19 17 18 21  20];   %数据集y轴值
s = polyfit(datasetx,datasety,1);                          %最小二乘拟合
figure();
plot(datasetx,datasety,'o');                               %绘制点
hold on;
y1 = polyval(s,datasetx);                                  %最小二乘计算的模型对点进行估计
plot(datasetx,y1);
[maybe_inliersx,maybe_inliersy,maybe_outliersx,maybe_outliersy] = RandomNData(datasetx,datasety,2,27);       %挑选局内点和局外点
iterations = 20;                                           %迭代次数
k=0;
best_consensus_setx = [];
best_consensus_sety = [];
best_model_vec = [];
numof_inliersset = 0;                                     %numof_inliersset表示局内点的个数
while  k<iterations
    [maybe_inliersx,maybe_inliersy,maybe_outliersx,maybe_outliersy] = RandomNData(datasetx,datasety,2,30);
    s1 = polyfit(maybe_inliersx,maybe_inliersy,1);                          %最小二乘拟合
    [maybe_inliersx,maybe_inliersy] = AgreeWithModel(maybe_inliersx,maybe_inliersy,maybe_outliersx,maybe_outliersy,s1,4);      %判断一个点是否符合模型
    [m1,n1] = size(maybe_inliersx);
    if (m1 > numof_inliersset)
        numof_inliersset = m1;
        best_consensus_setx = maybe_inliersx;
        best_consensus_sety = maybe_inliersy;                              %最佳模型参数保存                                              
    end
    k=k+1;
end
best_model_vec = polyfit(best_consensus_setx,best_consensus_sety,1); 
y2 = polyval(best_model_vec,datasetx);
plot(datasetx,y2,'r');
