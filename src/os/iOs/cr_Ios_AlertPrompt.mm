#ifdef IPHONE_ENVIRONMENT

#import "cr_Ios_AlertPrompt.h"

@implementation Cran_Ios_AlertPrompt
@synthesize textField = textField_;
@synthesize enteredText;

int cranShowAlert(void *p_objectInstance)
{

    Cran_Ios_AlertPrompt *prompt = [Cran_Ios_AlertPrompt alloc];
    prompt = [prompt initWithTitle:@"Enter Initials" message:@"Initials" delegate:(id)p_objectInstance cancelButtonTitle:@"Enter"];
    [prompt show];
    [prompt release];

    return 1;
    //*********************
}

- (id)initWithTitle:(NSString *)title message:(NSString *)message delegate:(id)delegate cancelButtonTitle:(NSString *)cancelButtonTitle
{
    
    self = [super initWithTitle:title message:@"\n" delegate:delegate cancelButtonTitle:@"Enter" otherButtonTitles:nil];
    //
    UITextField *theTextField = [[UITextField alloc] initWithFrame:CGRectMake(12.0, 30.0, 260.0, 25.0)]; 
    [theTextField setBackgroundColor:[UIColor whiteColor]]; 
    //[theTextField setText:message];
    [self addSubview:theTextField];
    self.textField = theTextField;
    textField_.delegate = self;
    
    [theTextField release];
    
    return self;
}

- (BOOL)textField:(UITextField *)textFieldPar shouldChangeCharactersInRange:(NSRange)range replacementString:(NSString *)string {
    
    if (textFieldPar.text.length >= 20 && range.length == 0)
    {
        return NO; // return NO to not change text
    } else {
        return YES;
    }
}

- (void)show
{
    [textField_ becomeFirstResponder];
    [super show];
}

- (NSString *)enteredText
{
    return textField_.text;
}

- (void)dealloc
{
    [textField_ release];
    [super dealloc];
}

@end

#endif