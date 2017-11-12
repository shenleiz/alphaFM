# -*- coding: utf-8 -*- 
'''
Created on 2017年9月8日

@author: thinkpad
'''
from sklearn import metrics
import time 
import sys
y_test=[]
pred=[]
with open(sys.argv[1],'r') as r:
    for i in r.readlines():
        info = i.rstrip().split(' ')
        label = info[0]
        tmp_pred=float(info[1])
        if label=='1':
            y_test.append(1)
        else:
            y_test.append(0)
        pred.append(tmp_pred)
all_num=len(y_test)

for i in range(1000):
    begin=i*1000000
    end=(i+1)*1000000
    if end>all_num:
        break
    y_test_tmp=y_test[begin:end]     
    pred_tmp=pred[begin:end] 
    fpr, tpr, thresholds = metrics.roc_curve(y_test_tmp, pred_tmp)
    auc = metrics.auc(fpr, tpr)        
    print 'end',time.ctime(),'auc:',auc  
if __name__ == '__main__':
    pass