%%%%%%%%%%%%%%%%%%%%%%%�����ݼ��������ȡn��ֵ%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% 
%datax     x�������ֵ
%datay     y�������ֵ
%Num        ���ɵ�������ĸ���
%Numtotal   �����ж�����
%maybe_inliersx    x����ڵ�
%maybe_inliersy    y����ڵ�
%maybe_outliersx   x������
%maybe_outliersy   y������
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function [maybe_inliersx,maybe_inliersy,maybe_outliersx,maybe_outliersy] = RandomNData(datax,datay,Num,Numtotal)
[m,n] = size(datax);
RandomNumLen = 100;                                        %���ɵ�������ĳ���
RandomMat = 1+(Numtotal-1)*rand(1,RandomNumLen);           %����100�������
RandomMat = round(RandomMat);
RandomMat_Num = zeros(1,Num);                              %������ѡNum�����ظ��������
k=1;
for i=1:RandomNumLen                                       %��ǰ�����֣���Num���������û���֣��ͼӽ�ȥ
   if((NumInVec(RandomMat(1,i),RandomMat_Num) == 0)&& (k<=Num) )
       RandomMat_Num(1,k) = RandomMat(1,i);
       k=k+1;
   end
end
tem_inx =[];
tem_iny =[];
tem_outx =[];
tem_outy =[];    
for i=1:n                                                   %��ȡNum����������ж�Ӧ��ֵ�����浽tem_inx��tem_iny������Num����������еı��浽tem_outx��tem_outy
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