%% CS294A/CS294W Self-taught Learning Exercise

%  Instructions
%  ------------
% 
%  This file contains code that helps you get started on the
%  self-taught learning. You will need to complete code in feedForwardAutoencoder.m
%  You will also need to have implemented sparseAutoencoderCost.m and 
%  softmaxCost.m from previous exercises.
%
%% ======================================================================
%  STEP 0: Here we provide the relevant parameters values that will
%  allow your sparse autoencoder to get good filters; you do not need to 
%  change the parameters below.

inputSize  = 28 * 28;
numLabels  = 5;
hiddenSize = 200;
sparsityParam = 0.1; % desired average activation of the hidden units.
                     % (This was denoted by the Greek alphabet rho, which looks like a lower-case "p",
		             %  in the lecture notes). 
lambda = 3e-3;       % weight decay parameter       
beta = 3;            % weight of sparsity penalty term   
maxIter = 400;

%% ======================================================================
%  STEP 1: Load data from the MNIST database
%
%  This loads our training and test data from the MNIST database files.
%  We have sorted the data for you in this so that you will not have to
%  change it.

% Load MNIST database files
%Code added by LiangJiang
addpath ../ex1
addpath ../common;
addpath(genpath('../common/minFunc_2012/minFunc'));
%%
mnistData   = loadMNISTImages('../common/train-images-idx3-ubyte');
mnistLabels = loadMNISTLabels('../common/train-labels-idx1-ubyte');
% Set Unlabeled Set (All Images)
figure('name', 'data');
display_network(mnistData(:, 1 : 200));
% Simulate a Labeled and Unlabeled set
labeledSet   = find(mnistLabels >= 0 & mnistLabels <= 4);
unlabeledSet = find(mnistLabels >= 5);

numTrain = round(numel(labeledSet)/2);
trainSet = labeledSet(1:numTrain);
testSet  = labeledSet(numTrain+1:end);

unlabeledData = mnistData(:, unlabeledSet);

trainData   = mnistData(:, trainSet);
trainLabels = mnistLabels(trainSet)' + 1; % Shift Labels to the Range 1-5

testData   = mnistData(:, testSet);
testLabels = mnistLabels(testSet)' + 1;   % Shift Labels to the Range 1-5

% Output Some Statistics
fprintf('# examples in unlabeled set: %d\n', size(unlabeledData, 2));
fprintf('# examples in supervised training set: %d\n\n', size(trainData, 2));
fprintf('# examples in supervised testing set: %d\n\n', size(testData, 2));

%% ======================================================================
%  STEP 2: Train the sparse autoencoder
%  This trains the sparse autoencoder on the unlabeled training
%  images. 

%  Randomly initialize the parameters
theta = initializeParameters(hiddenSize, inputSize);


%% ----------------- YOUR CODE HERE ----------------------
%  Find opttheta by running the sparse autoencoder on
%  unlabeledTrainingImages
options.Method = 'lbfgs'; % Here, we use L-BFGS to optimize our cost
                          % function. Generally, for minFunc to work, you
                          % need a function pointer with two outputs: the
                          % function value and the gradient. In our problem,
                          % sparseAutoencoderCost.m satisfies this.
options.maxIter = 400;	  % Maximum number of iterations of L-BFGS to run 
options.display = 'on';
%[theta, cost] = minFunc(@(x)sparseAutoencoderCost(x, inputSize, hiddenSize, lambda, sparsityParam, beta, trainData), theta, options);

%opttheta = theta; 
%save('opttheta', 'opttheta');
load opttheta;







%% -----------------------------------------------------
                          
% Visualize weights
W1 = reshape(opttheta(1:hiddenSize * inputSize), hiddenSize, inputSize);
%load W1;
%opttheta = W1(:);
fprintf('display_network\n');
figure('name', 'selfW1');
display_network(W1');

%%======================================================================
%% STEP 3: Extract Features from the Supervised Dataset
%  
%  You need to complete the code in feedForwardAutoencoder.m so that the 
%  following command will extract features from the data.

trainFeatures = feedForwardAutoencoder(opttheta, hiddenSize, inputSize, ...
                                       trainData);

testFeatures = feedForwardAutoencoder(opttheta, hiddenSize, inputSize, ...
                                       testData);

%%======================================================================
%% STEP 4: Train the softmax classifier

softmaxModel = struct;  
%% ----------------- YOUR CODE HERE ----------------------
%  Use softmaxTrain.m from the previous exercise to train a multi-class
%  classifier. 

%  Use lambda = 1e-4 for the weight regularization for softmax

% You need to compute softmaxModel using softmaxTrain on trainFeatures and
% trainLabels
options.maxIter = 100;
trainFeatures = [ones(1, size(trainFeatures, 2)); trainFeatures];
testFeatures = [ones(1, size(testFeatures, 2)); testFeatures];
n = size(trainFeatures, 1);
softmaxTheta = rand(n, 9) * 0.001;
options = struct('MaxIter', 200);
softmaxTheta(:) = minFunc(@softmax_regression_vec, softmaxTheta(:), options, trainFeatures, trainLabels);
softmaxTheta = [softmaxTheta, zeros(n, 1)];








%% -----------------------------------------------------


%%======================================================================
%% STEP 5: Testing 

%% ----------------- YOUR CODE HERE ----------------------
% Compute Predictions on the test set (testFeatures) using softmaxPredict
% and softmaxModel

accuracy = multi_classifier_accuracy(softmaxTheta, testFeatures, testLabels);
fprintf('Test accuracy: %2.1f%%\n', 100 * accuracy);












%% -----------------------------------------------------

% Classification Score
%fprintf('Test Accuracy: %f%%\n', 100*mean(pred(:) == testLabels(:)));

% (note that we shift the labels by 1, so that digit 0 now corresponds to
%  label 1)
%
% Accuracy is the proportion of correctly classified images
% The results for our implementation was:
%
% Accuracy: 98.3%
%
% 
