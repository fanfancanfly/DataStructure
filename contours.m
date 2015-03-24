clc;
clear all;
img =imread('C:\Users\xiefanfan\Desktop\20150322\DSC03953.JPG');
img_r = img(:,:,1);
img_g = img(:,:,2);
img_b = img(:,:,3);
[m,n,k] = size(img);
img_flag = zeros(m,n);
for i=1:m
    for j=1:n
        if ((img_b(i,j) > img_r(i,j)*1.5) && (img_b(i,j) > img_g(i,j)*1.5)) && img_b(i,j) > 180
            img_flag(i,j)=255;
        else
            img_flag(i,j)=0;
        end
    end
end
imwrite(img_flag,'C:\Users\xiefanfan\Desktop\20150322\DSC03953coun.JPG','jpg');
figure();
imshow(img);
figure();
imshow(img_flag);