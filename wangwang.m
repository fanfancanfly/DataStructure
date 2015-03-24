
function wangwang()
[filename, pathname] = uigetfile( ...
    {'*.jpg;*.tif;*.png;*.gif','All Image Files';...
    '*.*','All Files' },...
    '请选择要修改的图片（可多选）', ...
    'MultiSelect', 'on');

if ~iscell(filename)
    filename1{1}=filename;
else
    filename1=filename;
end

A=imread(strcat(pathname,filename1{1}));
r = A(:, :, 1);
g = A(:, :, 2);
b = A(:, :, 3);
C=0.2989 * r + 0.5870 * g + 0.1140 * b ;
imshow(C);
imwrite(C,'C:\Users\Administrator\Desktop\IMg.jpg');
end
