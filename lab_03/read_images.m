function [image_sandwich, image_Y, image_X] = read_images()
    image_pull = dir('C:\temp\lab_3\SpectralDeltaE\*.tif');
    if (isempty(image_pull))
        error('Check path to images');
    end
    image_count = length(image_pull);
    image = imresize(imread(strcat('C:\temp\lab_3\SpectralDeltaE\', image_pull(1).name)), 0.25);
    
    [image_Y, image_X] = size(image);
    image_sandwich = zeros(image_Y, image_X, image_count);
    image_sandwich(:,:,1) = image;
    clear image
    for i = 2:image_count
        image_sandwich(:,:,i) = ...;
        imresize(imread(strcat('C:\temp\lab_3\SpectralDeltaE\', image_pull(i).name)), 0.25);
    end

end