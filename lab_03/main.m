clc
clear
close all

%% 2. Загрузка изображений
[image_sandwich, image_Y, image_X] = read_images();

%% 3. Расчет XYZ
% Загрузка таблиц
lambda_start = 480;
lambda_step = 2;
lambda_end = 110;
LAMBDA = lambda_start:lambda_step:lambda_end;

CIE_XYZ_1931 = xlsread('CIE tables.xls', 4);
CIE_XYZ_1931 = CIE_XYZ_1931(ismember(CIE_XYZ_1931(:,1), LAMBDA), :);

I_lambda = xlsread('CIE tables.xls', 1);
I_lambda = I_lambda(ismember(I_lambda(:, 1), LAMBDA), :);

% Непосредственное вычисление XYZ

% I_lambda_type: 2 - A, 3 - D65, 4 - C
I_lambda_type = 3;

image_result = zeros(image_Y, image_X, 3);

x_topline = CIE_XYZ_1931(:, 2);
y_topline = CIE_XYZ_1931(:, 3);
z_topline = CIE_XYZ_1931(:, 4);

N = sum(y_topline .* I_lambda(:, I_lambda_type));

for y = 1:image_Y
    for x = 1:image_X
        image_sandwich_to_column = squeeze(image_sandwich(y, x, :));
        X = 1/N * sum(x_topline .* I_lambda(:, I_lambda_type) .* image_sandwich_to_column);
        Y = 1/N * sum(y_topline .* I_lambda(:, I_lambda_type) .* image_sandwich_to_column);
        Z = 1/N * sum(z_topline .* I_lambda(:, I_lambda_type) .* image_sandwich_to_column);
        image_result(y, x, :) = [X Y Z];
    end
end

%clear image_sandwich  image_sandwich_to_column

% 4-7. Переход от XYZ к RGB
figure;
image1 = XYZ_to_RGB(image_result, 1);
imshow(image1);

figure;
image2 = XYZ_to_RGB(image_result, 2);
imshow(image2);
%xyz2rgb
figure;
image3 = XYZ_to_RGB(image_result, 3);
imshow(image3);

%% 8. Метамерные цвета
x1 = 445; y1 = 16;
x2 = 460; y2 = 19;
Splot(LAMBDA, x1*4, y1*4, x2*4, y2*4);
