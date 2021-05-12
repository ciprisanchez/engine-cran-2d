#ifdef IPHONE_ENVIRONMENT

#ifndef __IOS_ALERTPROMPT_H__
#define __IOS_ALERTPROMPT_H__

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#import "crOsIosInterface.h"

@interface Cran_Ios_AlertPrompt : UIAlertView <UITextFieldDelegate>
{
    UITextField *textField_;
}

@property (nonatomic, retain) UITextField *textField;
@property (readonly) NSString *enteredText;

- (id)initWithTitle:(NSString *)title message:(NSString *)message delegate:(id)op cancelButtonTitle:(NSString *)cancelButtonTitle;


@end
#endif
#endif