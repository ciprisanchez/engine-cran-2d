#ifdef IPHONE_ENVIRONMENT
/*
#import "cr_Ios_AlertPromptDelegate.h"

@implementation Cran_Ios_AlertPromptDelegate
@synthesize delegate = delegate_;

- (void)alertView:(UIAlertView *)alertView willDismissWithButtonIndex:(NSInteger)buttonIndex
//- (void)willDismissWithButtonIndex:(NSInteger)buttonIndex
{
    
    NSString *filePath = @"";
    NSString *alias = @"";//enteredText;
    NSString *aliasLowercase = @"";//[alias lowercaseString];
    /*
    NSString *alias = [(AlertPrompt *)alertView enteredText];
    NSString *aliasLowercase = [alias lowercaseString];
    aliasLowercase = [aliasLowercase stringByReplacingOccurrencesOfString:@"€" withString:@" "];
    */
    /*
    //
    if (cranBridge_->BRIDGE_IS_LEVEL_EASY() || cranBridge_->BRIDGE_IS_LEVEL_INITIAL_EASY()){
        if (cranBridge_->BRIDGE_IS_LEVEL_SINGLE()){
            //filePath = @(GameCommons::GAME_FILE_EASY_SINGLE);
            filePath = [NSString stringWithUTF8String:GameCommons::GAME_FILE_EASY_SINGLE];
        } else if (cranBridge_->BRIDGE_IS_LEVEL_MULTI()){
            filePath = [NSString stringWithUTF8String:GameCommons::GAME_FILE_EASY_MULTI];
            //filePath = GameCommons::GAME_FILE_EASY_MULTI;
        }
    } else if (cranBridge_->BRIDGE_IS_LEVEL_HARD()){
        if (cranBridge_->BRIDGE_IS_LEVEL_SINGLE()){
            filePath = [NSString stringWithUTF8String:GameCommons::GAME_FILE_HARD_SINGLE];
            //filePath = GameCommons::GAME_FILE_HARD_SINGLE;
        } else if (cranBridge_->BRIDGE_IS_LEVEL_MULTI()){
            filePath = [NSString stringWithUTF8String:GameCommons::GAME_FILE_HARD_MULTI];
            //filePath = GameCommons::GAME_FILE_HARD_MULTI;
        }
    }
    //
    NSMutableString* filePathMutable = [NSMutableString string];
    [filePathMutable appendString:filePath];
    //
    //cranBridge_->_game-> game_file_start([filePathMutable cStringUsingEncoding:1], [aliasLowercase UTF8String]);
    GameFile::game_file_start([filePathMutable cStringUsingEncoding:1], [aliasLowercase UTF8String]);
     
}
@end
*/
#endif