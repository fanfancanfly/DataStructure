%%%%%%%%%%%%%%%%%%%%%%%%%%%%��ʵ�����RANSAC�㷨%%%%%%%%%%%%%%%%%%%%%%%%%%%%
clc;
clear all;
close all;
datasetx = [1 2 3 4 5 5 7 8 9  9 11 12 13 15 15 16 17 18 19  2 3   4 7  8 9 10 11 12 13 14];    %���ݼ�x��ֵ
datasety = [1 2 2 4 5 6 7 8 9 10 11 10 14 14 15 17 17 19 19 16 14 18 15 3 4 19 17 18 21  20];   %���ݼ�y��ֵ
s = polyfit(datasetx,datasety,1);                          %��С�������
figure();
plot(datasetx,datasety,'o');                               %���Ƶ�
hold on;
y1 = polyval(s,datasetx);                                  %��С���˼����ģ�ͶԵ���й���
plot(datasetx,y1);
[maybe_inliersx,maybe_inliersy,maybe_outliersx,maybe_outliersy] = RandomNData(datasetx,datasety,2,27);       %��ѡ���ڵ�;����
iterations = 20;                                           %��������
k=0;
best_consensus_setx = [];
best_consensus_sety = [];
best_model_vec = [];
numof_inliersset = 0;                                     %numof_inliersset��ʾ���ڵ�ĸ���
while  k<iterations
    [maybe_inliersx,maybe_inliersy,maybe_outliersx,maybe_outliersy] = RandomNData(datasetx,datasety,2,30);
    s1 = polyfit(maybe_inliersx,maybe_inliersy,1);                          %��С�������
    [maybe_inliersx,maybe_inliersy] = AgreeWithModel(maybe_inliersx,maybe_inliersy,maybe_outliersx,maybe_outliersy,s1,4);      %�ж�һ�����Ƿ����ģ��
    [m1,n1] = size(maybe_inliersx);
    if (m1 > numof_inliersset)
        numof_inliersset = m1;
        best_consensus_setx = maybe_inliersx;
        best_consensus_sety = maybe_inliersy;                              %���ģ�Ͳ�������                                              
    end
    k=k+1;
end
best_model_vec = polyfit(best_consensus_setx,best_consensus_sety,1); 
y2 = polyval(best_model_vec,datasetx);
plot(datasetx,y2,'r');
