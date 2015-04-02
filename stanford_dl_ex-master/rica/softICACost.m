%% Your job is to implement the RICA cost and gradient
function [cost,grad] = softICACost(theta, x, params)

% unpack weight matrix
W = reshape(theta, params.numFeatures, params.n);

% project weights to norm ball (prevents degenerate bases)
Wold = W;
W = l2rowscaled(W, 1);
epsilon = 0.01;
%%% YOUR CODE HERE %%%
lambda = params.lambda;
temp1 = W * x;
temp2 = W' * temp1 - x;
cost1 = sqrt(temp1 .^ 2 + epsilon);
cost1 = lambda * norm(cost1, 1);
cost2 = 0.5 * norm(temp2, 2) .^ 2;
cost = lambda * cost1 + cost2;

Wgrad = W * (2 * temp2) * x' +  2 * temp1 * temp2';
% unproject gradient for minFunc
grad = l2rowscaledg(Wold, W, Wgrad, 1);
grad = grad(:);
