%%%%%%%%%%%%%%%%%%%%%%%从数据集中随机抽取n个值%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% 
%datax     x坐标轴的值
%datay     y坐标轴的值
%Num        生成的随机数的个数
%Numtotal   数据有多少数
%maybe_inliersx    x轴局内点
%maybe_inliersy    y轴局内点
%maybe_outliersx   x轴局外点
%maybe_outliersy   y轴局外点
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function [maybe_inliersx,maybe_inliersy,maybe_outliersx,maybe_outliersy] = RandomNData(datax,datay,Num,Numtotal)
[m,n] = size(datax);
RandomNumLen = 100;                                        %生成的随机数的长度
RandomMat = 1+(Numtotal-1)*rand(1,RandomNumLen);           %生成100个随机数
RandomMat = round(RandomMat);
RandomMat_Num = zeros(1,Num);                              %从中挑选Num个不重复的随机数
k=1;
for i=1:RandomNumLen                                       %当前的数字，在Num个随机数中没出现，就加进去
   if((NumInVec(RandomMat(1,i),RandomMat_Num) == 0)&& (k<=Num) )
       RandomMat_Num(1,k) = RandomMat(1,i);
       k=k+1;
   end
end
tem_inx =[];
tem_iny =[];
tem_outx =[];
tem_outy =[];    
for i=1:n                                                   %提取Num个随机数字中对应行值，保存到tem_inx，tem_iny，不是Num个随机数字中的保存到tem_outx，tem_outy
    if(NumInVec(i,RandomMat_Num) > 0)
        tem_inx = [tem_inx;datax(1,i)];
        tem_iny = [tem_iny;datay(1,i)];
    else
        tem_outx = [tem_outx;datax(1,i)];
        tem_outy = [tem_outy;datay(1,i)];
    end
end
maybe_inliersx = tem_inx;
maybe_inliersy = tem_iny;
maybe_outliersx = tem_outx;
maybe_outliersy = tem_outy;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%