function [image_result] = XYZ_to_RGB(image, source_type)
    [image_Y, image_X, image_Z] = size(image);
    image_result = zeros(image_Y, image_X, image_Z);
    image_result(:, :, 1) = image(:, :, 1) / ...
        max(reshape(image(:, :, 1), image_Y * image_X, []));
    image_result(:, :, 2) = image(: ,:, 2) / ...
        max(reshape(image(:, :, 2), image_Y * image_X, []));
    image_result(:, :, 3) = image(:, :, 3) / ...
        max(reshape(image(:, :, 3), image_Y * image_X, []));
    M_params = num2cell(xlsread('M_and_white.xls'));
    if (isempty(M_params))
        error('Check if table with M parameters exists');
    end
    [xr, yr, xg, yg, xb, yb, Xw, Yw] = M_params{source_type, :};
    Xr = xr / yr;
    Yr = 1;
    Zr = (1-xr-yr) / yr;

    Xg = xg / yg;
    Yg = 1;
    Zg = (1-xg-yg) / yg;

    Xb = xb / yb;
    Yb = 1;
    Zb = (1-xb-yb) / yb;

    Srgb = num2cell([Xr Xg Xb; Yr Yg Yb; Zr Zg Zb] \ [Xw; Yw; 1-Xw-Yw]);
    [Sr, Sg, Sb] = Srgb{:};
    M = [ Sr*Xr Sg*Xg Sb*Xb; Sr*Yr Sg*Yg Sb*Yb; Sr*Zr Sg*Zg Sb*Zb ];

    for y = 1:image_Y
        for x = 1:image_X
            rgb = M\reshape(image_result(y, x, :), 3, []);
            image_result(y, x, :) = rgb(:);
        end
    end
    image_result = imadjust(image_result, [], [], 1/2.2);
    image_result = uint8(image_result*255);
end