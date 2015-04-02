function [Z] = zca2(x)
epsilon = 1e-4;
% You should be able to use the code from your PCA/ZCA exercise
% Retain all of the components from the ZCA transform (i.e. do not do
% dimensionality reduction)

% x is the input patch data of size
% z is the ZCA transformed data. The dimenison of z = x.

%%% YOUR CODE HERE %%%
temp = mean(x, 1);
temp = repmat(temp, size(x, 1), 1);
x = x - temp;
sigma = x * x' / size(x, 2);
[U, S, V] = svd(sigma);
xRot = U' * x;
eigenValues = diag(S);
tempEigenV = sqrt(eigenValues + epsilon);
xPca = bsxfun(@rdivide, xRot, tempEigenV);
Z = U * xPca;

