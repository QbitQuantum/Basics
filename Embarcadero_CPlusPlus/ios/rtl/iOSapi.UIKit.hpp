// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'iOSapi.UIKit.pas' rev: 34.00 (iOS)

#ifndef Iosapi_UikitHPP
#define Iosapi_UikitHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <iOSapi.CocoaTypes.hpp>
#include <Macapi.CoreFoundation.hpp>
#include <iOSapi.Foundation.hpp>
#include <Macapi.ObjCRuntime.hpp>
#include <Macapi.ObjectiveC.hpp>
#include <iOSapi.QuartzCore.hpp>
#include <iOSapi.CoreData.hpp>
#include <iOSapi.CoreGraphics.hpp>
#include <iOSapi.CoreImage.hpp>
#include <iOSapi.CoreText.hpp>
#include <System.Rtti.hpp>

//-- user supplied -----------------------------------------------------------

namespace Iosapi
{
namespace Uikit
{
//-- forward type declarations -----------------------------------------------
struct UIEdgeInsets;
struct UIOffset;
__interface DELPHIINTERFACE NSLayoutConstraintClass;
typedef System::DelphiInterface<NSLayoutConstraintClass> _di_NSLayoutConstraintClass;
__interface DELPHIINTERFACE NSLayoutConstraint;
typedef System::DelphiInterface<NSLayoutConstraint> _di_NSLayoutConstraint;
class DELPHICLASS TNSLayoutConstraint;
__interface DELPHIINTERFACE NSLayoutManagerClass;
typedef System::DelphiInterface<NSLayoutManagerClass> _di_NSLayoutManagerClass;
__interface DELPHIINTERFACE NSLayoutManager;
typedef System::DelphiInterface<NSLayoutManager> _di_NSLayoutManager;
class DELPHICLASS TNSLayoutManager;
__interface DELPHIINTERFACE NSTextStorageClass;
typedef System::DelphiInterface<NSTextStorageClass> _di_NSTextStorageClass;
__interface DELPHIINTERFACE NSTextStorage;
typedef System::DelphiInterface<NSTextStorage> _di_NSTextStorage;
class DELPHICLASS TNSTextStorage;
__interface DELPHIINTERFACE UIFontDescriptorClass;
typedef System::DelphiInterface<UIFontDescriptorClass> _di_UIFontDescriptorClass;
__interface DELPHIINTERFACE UIFontDescriptor;
typedef System::DelphiInterface<UIFontDescriptor> _di_UIFontDescriptor;
class DELPHICLASS TUIFontDescriptor;
__interface DELPHIINTERFACE NSTextContainerClass;
typedef System::DelphiInterface<NSTextContainerClass> _di_NSTextContainerClass;
__interface DELPHIINTERFACE NSTextContainer;
typedef System::DelphiInterface<NSTextContainer> _di_NSTextContainer;
class DELPHICLASS TNSTextContainer;
__interface DELPHIINTERFACE NSTextTabClass;
typedef System::DelphiInterface<NSTextTabClass> _di_NSTextTabClass;
__interface DELPHIINTERFACE NSTextTab;
typedef System::DelphiInterface<NSTextTab> _di_NSTextTab;
class DELPHICLASS TNSTextTab;
__interface DELPHIINTERFACE NSParagraphStyleClass;
typedef System::DelphiInterface<NSParagraphStyleClass> _di_NSParagraphStyleClass;
__interface DELPHIINTERFACE NSParagraphStyle;
typedef System::DelphiInterface<NSParagraphStyle> _di_NSParagraphStyle;
class DELPHICLASS TNSParagraphStyle;
__interface DELPHIINTERFACE NSMutableParagraphStyleClass;
typedef System::DelphiInterface<NSMutableParagraphStyleClass> _di_NSMutableParagraphStyleClass;
__interface DELPHIINTERFACE NSMutableParagraphStyle;
typedef System::DelphiInterface<NSMutableParagraphStyle> _di_NSMutableParagraphStyle;
class DELPHICLASS TNSMutableParagraphStyle;
__interface DELPHIINTERFACE NSShadowClass;
typedef System::DelphiInterface<NSShadowClass> _di_NSShadowClass;
__interface DELPHIINTERFACE NSShadow;
typedef System::DelphiInterface<NSShadow> _di_NSShadow;
class DELPHICLASS TNSShadow;
__interface DELPHIINTERFACE NSStringDrawingContextClass;
typedef System::DelphiInterface<NSStringDrawingContextClass> _di_NSStringDrawingContextClass;
__interface DELPHIINTERFACE NSStringDrawingContext;
typedef System::DelphiInterface<NSStringDrawingContext> _di_NSStringDrawingContext;
class DELPHICLASS TNSStringDrawingContext;
__interface DELPHIINTERFACE NSTextAttachmentClass;
typedef System::DelphiInterface<NSTextAttachmentClass> _di_NSTextAttachmentClass;
__interface DELPHIINTERFACE NSTextAttachment;
typedef System::DelphiInterface<NSTextAttachment> _di_NSTextAttachment;
class DELPHICLASS TNSTextAttachment;
__interface DELPHIINTERFACE UIKeyCommandClass;
typedef System::DelphiInterface<UIKeyCommandClass> _di_UIKeyCommandClass;
__interface DELPHIINTERFACE UIKeyCommand;
typedef System::DelphiInterface<UIKeyCommand> _di_UIKeyCommand;
class DELPHICLASS TUIKeyCommand;
__interface DELPHIINTERFACE UITextInputModeClass;
typedef System::DelphiInterface<UITextInputModeClass> _di_UITextInputModeClass;
__interface DELPHIINTERFACE UITextInputMode;
typedef System::DelphiInterface<UITextInputMode> _di_UITextInputMode;
class DELPHICLASS TUITextInputMode;
__interface DELPHIINTERFACE UIKitAdditions;
typedef System::DelphiInterface<UIKitAdditions> _di_UIKitAdditions;
__interface DELPHIINTERFACE UITraitCollectionClass;
typedef System::DelphiInterface<UITraitCollectionClass> _di_UITraitCollectionClass;
__interface DELPHIINTERFACE UITraitCollection;
typedef System::DelphiInterface<UITraitCollection> _di_UITraitCollection;
class DELPHICLASS TUITraitCollection;
__interface DELPHIINTERFACE UITraitEnvironmentClass;
typedef System::DelphiInterface<UITraitEnvironmentClass> _di_UITraitEnvironmentClass;
__interface DELPHIINTERFACE UITraitEnvironment;
typedef System::DelphiInterface<UITraitEnvironment> _di_UITraitEnvironment;
class DELPHICLASS TUITraitEnvironment;
__interface DELPHIINTERFACE UIDynamicAnimatorClass;
typedef System::DelphiInterface<UIDynamicAnimatorClass> _di_UIDynamicAnimatorClass;
__interface DELPHIINTERFACE UIDynamicAnimator;
typedef System::DelphiInterface<UIDynamicAnimator> _di_UIDynamicAnimator;
class DELPHICLASS TUIDynamicAnimator;
__interface DELPHIINTERFACE UIDynamicBehaviorClass;
typedef System::DelphiInterface<UIDynamicBehaviorClass> _di_UIDynamicBehaviorClass;
__interface DELPHIINTERFACE UIDynamicBehavior;
typedef System::DelphiInterface<UIDynamicBehavior> _di_UIDynamicBehavior;
class DELPHICLASS TUIDynamicBehavior;
__interface DELPHIINTERFACE UIMenuItemClass;
typedef System::DelphiInterface<UIMenuItemClass> _di_UIMenuItemClass;
__interface DELPHIINTERFACE UIMenuItem;
typedef System::DelphiInterface<UIMenuItem> _di_UIMenuItem;
class DELPHICLASS TUIMenuItem;
__interface DELPHIINTERFACE UIMenuControllerClass;
typedef System::DelphiInterface<UIMenuControllerClass> _di_UIMenuControllerClass;
__interface DELPHIINTERFACE UIMenuController;
typedef System::DelphiInterface<UIMenuController> _di_UIMenuController;
class DELPHICLASS TUIMenuController;
__interface DELPHIINTERFACE UINibClass;
typedef System::DelphiInterface<UINibClass> _di_UINibClass;
__interface DELPHIINTERFACE UINib;
typedef System::DelphiInterface<UINib> _di_UINib;
class DELPHICLASS TUINib;
__interface DELPHIINTERFACE UINavigationItemClass;
typedef System::DelphiInterface<UINavigationItemClass> _di_UINavigationItemClass;
__interface DELPHIINTERFACE UINavigationItem;
typedef System::DelphiInterface<UINavigationItem> _di_UINavigationItem;
class DELPHICLASS TUINavigationItem;
__interface DELPHIINTERFACE UITextCheckerClass;
typedef System::DelphiInterface<UITextCheckerClass> _di_UITextCheckerClass;
__interface DELPHIINTERFACE UITextChecker;
typedef System::DelphiInterface<UITextChecker> _di_UITextChecker;
class DELPHICLASS TUITextChecker;
__interface DELPHIINTERFACE UILocalizedIndexedCollationClass;
typedef System::DelphiInterface<UILocalizedIndexedCollationClass> _di_UILocalizedIndexedCollationClass;
__interface DELPHIINTERFACE UILocalizedIndexedCollation;
typedef System::DelphiInterface<UILocalizedIndexedCollation> _di_UILocalizedIndexedCollation;
class DELPHICLASS TUILocalizedIndexedCollation;
__interface DELPHIINTERFACE UIImageClass;
typedef System::DelphiInterface<UIImageClass> _di_UIImageClass;
__interface DELPHIINTERFACE UIImage;
typedef System::DelphiInterface<UIImage> _di_UIImage;
class DELPHICLASS TUIImage;
__interface DELPHIINTERFACE UIGestureRecognizerClass;
typedef System::DelphiInterface<UIGestureRecognizerClass> _di_UIGestureRecognizerClass;
__interface DELPHIINTERFACE UIGestureRecognizer;
typedef System::DelphiInterface<UIGestureRecognizer> _di_UIGestureRecognizer;
class DELPHICLASS TUIGestureRecognizer;
__interface DELPHIINTERFACE UIFontClass;
typedef System::DelphiInterface<UIFontClass> _di_UIFontClass;
__interface DELPHIINTERFACE UIFont;
typedef System::DelphiInterface<UIFont> _di_UIFont;
class DELPHICLASS TUIFont;
__interface DELPHIINTERFACE UILocalNotificationClass;
typedef System::DelphiInterface<UILocalNotificationClass> _di_UILocalNotificationClass;
__interface DELPHIINTERFACE UILocalNotification;
typedef System::DelphiInterface<UILocalNotification> _di_UILocalNotification;
class DELPHICLASS TUILocalNotification;
__interface DELPHIINTERFACE UIUserNotificationSettingsClass;
typedef System::DelphiInterface<UIUserNotificationSettingsClass> _di_UIUserNotificationSettingsClass;
__interface DELPHIINTERFACE UIUserNotificationSettings;
typedef System::DelphiInterface<UIUserNotificationSettings> _di_UIUserNotificationSettings;
class DELPHICLASS TUIUserNotificationSettings;
__interface DELPHIINTERFACE UITextInputStringTokenizerClass;
typedef System::DelphiInterface<UITextInputStringTokenizerClass> _di_UITextInputStringTokenizerClass;
__interface DELPHIINTERFACE UITextInputStringTokenizer;
typedef System::DelphiInterface<UITextInputStringTokenizer> _di_UITextInputStringTokenizer;
class DELPHICLASS TUITextInputStringTokenizer;
__interface DELPHIINTERFACE UITextRangeClass;
typedef System::DelphiInterface<UITextRangeClass> _di_UITextRangeClass;
__interface DELPHIINTERFACE UITextRange;
typedef System::DelphiInterface<UITextRange> _di_UITextRange;
class DELPHICLASS TUITextRange;
__interface DELPHIINTERFACE UIScreenModeClass;
typedef System::DelphiInterface<UIScreenModeClass> _di_UIScreenModeClass;
__interface DELPHIINTERFACE UIScreenMode;
typedef System::DelphiInterface<UIScreenMode> _di_UIScreenMode;
class DELPHICLASS TUIScreenMode;
__interface DELPHIINTERFACE UIScreenClass;
typedef System::DelphiInterface<UIScreenClass> _di_UIScreenClass;
__interface DELPHIINTERFACE UIScreen;
typedef System::DelphiInterface<UIScreen> _di_UIScreen;
class DELPHICLASS TUIScreen;
__interface DELPHIINTERFACE UIResponderClass;
typedef System::DelphiInterface<UIResponderClass> _di_UIResponderClass;
__interface DELPHIINTERFACE UIResponder;
typedef System::DelphiInterface<UIResponder> _di_UIResponder;
class DELPHICLASS TUIResponder;
__interface DELPHIINTERFACE UIStoryboardClass;
typedef System::DelphiInterface<UIStoryboardClass> _di_UIStoryboardClass;
__interface DELPHIINTERFACE UIStoryboard;
typedef System::DelphiInterface<UIStoryboard> _di_UIStoryboard;
class DELPHICLASS TUIStoryboard;
__interface DELPHIINTERFACE UISearchDisplayControllerClass;
typedef System::DelphiInterface<UISearchDisplayControllerClass> _di_UISearchDisplayControllerClass;
__interface DELPHIINTERFACE UISearchDisplayController;
typedef System::DelphiInterface<UISearchDisplayController> _di_UISearchDisplayController;
class DELPHICLASS TUISearchDisplayController;
__interface DELPHIINTERFACE UIStoryboardSegueClass;
typedef System::DelphiInterface<UIStoryboardSegueClass> _di_UIStoryboardSegueClass;
__interface DELPHIINTERFACE UIStoryboardSegue;
typedef System::DelphiInterface<UIStoryboardSegue> _di_UIStoryboardSegue;
class DELPHICLASS TUIStoryboardSegue;
__interface DELPHIINTERFACE UIPresentationControllerClass;
typedef System::DelphiInterface<UIPresentationControllerClass> _di_UIPresentationControllerClass;
__interface DELPHIINTERFACE UIPresentationController;
typedef System::DelphiInterface<UIPresentationController> _di_UIPresentationController;
class DELPHICLASS TUIPresentationController;
__interface DELPHIINTERFACE UIPopoverPresentationControllerClass;
typedef System::DelphiInterface<UIPopoverPresentationControllerClass> _di_UIPopoverPresentationControllerClass;
__interface DELPHIINTERFACE UIPopoverPresentationController;
typedef System::DelphiInterface<UIPopoverPresentationController> _di_UIPopoverPresentationController;
class DELPHICLASS TUIPopoverPresentationController;
__interface DELPHIINTERFACE UIPrintPaperClass;
typedef System::DelphiInterface<UIPrintPaperClass> _di_UIPrintPaperClass;
__interface DELPHIINTERFACE UIPrintPaper;
typedef System::DelphiInterface<UIPrintPaper> _di_UIPrintPaper;
class DELPHICLASS TUIPrintPaper;
__interface DELPHIINTERFACE UIPrintFormatterClass;
typedef System::DelphiInterface<UIPrintFormatterClass> _di_UIPrintFormatterClass;
__interface DELPHIINTERFACE UIPrintFormatter;
typedef System::DelphiInterface<UIPrintFormatter> _di_UIPrintFormatter;
class DELPHICLASS TUIPrintFormatter;
__interface DELPHIINTERFACE UIPopoverControllerClass;
typedef System::DelphiInterface<UIPopoverControllerClass> _di_UIPopoverControllerClass;
__interface DELPHIINTERFACE UIPopoverController;
typedef System::DelphiInterface<UIPopoverController> _di_UIPopoverController;
class DELPHICLASS TUIPopoverController;
__interface DELPHIINTERFACE UIPasteboardClass;
typedef System::DelphiInterface<UIPasteboardClass> _di_UIPasteboardClass;
__interface DELPHIINTERFACE UIPasteboard;
typedef System::DelphiInterface<UIPasteboard> _di_UIPasteboard;
class DELPHICLASS TUIPasteboard;
__interface DELPHIINTERFACE UILayoutGuide;
typedef System::DelphiInterface<UILayoutGuide> _di_UILayoutGuide;
__interface DELPHIINTERFACE UIViewClass;
typedef System::DelphiInterface<UIViewClass> _di_UIViewClass;
__interface DELPHIINTERFACE UIView;
typedef System::DelphiInterface<UIView> _di_UIView;
class DELPHICLASS TUIView;
__interface DELPHIINTERFACE UIPrinterClass;
typedef System::DelphiInterface<UIPrinterClass> _di_UIPrinterClass;
__interface DELPHIINTERFACE UIPrinter;
typedef System::DelphiInterface<UIPrinter> _di_UIPrinter;
class DELPHICLASS TUIPrinter;
__interface DELPHIINTERFACE UIPrinterPickerControllerClass;
typedef System::DelphiInterface<UIPrinterPickerControllerClass> _di_UIPrinterPickerControllerClass;
__interface DELPHIINTERFACE UIPrinterPickerController;
typedef System::DelphiInterface<UIPrinterPickerController> _di_UIPrinterPickerController;
class DELPHICLASS TUIPrinterPickerController;
__interface DELPHIINTERFACE UIPrintPageRendererClass;
typedef System::DelphiInterface<UIPrintPageRendererClass> _di_UIPrintPageRendererClass;
__interface DELPHIINTERFACE UIPrintPageRenderer;
typedef System::DelphiInterface<UIPrintPageRenderer> _di_UIPrintPageRenderer;
class DELPHICLASS TUIPrintPageRenderer;
__interface DELPHIINTERFACE UIPrintInteractionControllerClass;
typedef System::DelphiInterface<UIPrintInteractionControllerClass> _di_UIPrintInteractionControllerClass;
__interface DELPHIINTERFACE UIPrintInteractionController;
typedef System::DelphiInterface<UIPrintInteractionController> _di_UIPrintInteractionController;
class DELPHICLASS TUIPrintInteractionController;
__interface DELPHIINTERFACE UIPrintInfoClass;
typedef System::DelphiInterface<UIPrintInfoClass> _di_UIPrintInfoClass;
__interface DELPHIINTERFACE UIPrintInfo;
typedef System::DelphiInterface<UIPrintInfo> _di_UIPrintInfo;
class DELPHICLASS TUIPrintInfo;
__interface DELPHIINTERFACE UIBarItemClass;
typedef System::DelphiInterface<UIBarItemClass> _di_UIBarItemClass;
__interface DELPHIINTERFACE UIBarItem;
typedef System::DelphiInterface<UIBarItem> _di_UIBarItem;
class DELPHICLASS TUIBarItem;
__interface DELPHIINTERFACE UIBezierPathClass;
typedef System::DelphiInterface<UIBezierPathClass> _di_UIBezierPathClass;
__interface DELPHIINTERFACE UIBezierPath;
typedef System::DelphiInterface<UIBezierPath> _di_UIBezierPath;
class DELPHICLASS TUIBezierPath;
__interface DELPHIINTERFACE UIAccessibilityElementClass;
typedef System::DelphiInterface<UIAccessibilityElementClass> _di_UIAccessibilityElementClass;
__interface DELPHIINTERFACE UIAccessibilityElement;
typedef System::DelphiInterface<UIAccessibilityElement> _di_UIAccessibilityElement;
class DELPHICLASS TUIAccessibilityElement;
__interface DELPHIINTERFACE UIAccelerationClass;
typedef System::DelphiInterface<UIAccelerationClass> _di_UIAccelerationClass;
__interface DELPHIINTERFACE UIAcceleration;
typedef System::DelphiInterface<UIAcceleration> _di_UIAcceleration;
class DELPHICLASS TUIAcceleration;
__interface DELPHIINTERFACE UIAccelerometerClass;
typedef System::DelphiInterface<UIAccelerometerClass> _di_UIAccelerometerClass;
__interface DELPHIINTERFACE UIAccelerometer;
typedef System::DelphiInterface<UIAccelerometer> _di_UIAccelerometer;
class DELPHICLASS TUIAccelerometer;
__interface DELPHIINTERFACE UIDeviceClass;
typedef System::DelphiInterface<UIDeviceClass> _di_UIDeviceClass;
__interface DELPHIINTERFACE UIDevice;
typedef System::DelphiInterface<UIDevice> _di_UIDevice;
class DELPHICLASS TUIDevice;
__interface DELPHIINTERFACE UIDocumentClass;
typedef System::DelphiInterface<UIDocumentClass> _di_UIDocumentClass;
__interface DELPHIINTERFACE UIDocument;
typedef System::DelphiInterface<UIDocument> _di_UIDocument;
class DELPHICLASS TUIDocument;
__interface DELPHIINTERFACE UIEventClass;
typedef System::DelphiInterface<UIEventClass> _di_UIEventClass;
__interface DELPHIINTERFACE UIEvent;
typedef System::DelphiInterface<UIEvent> _di_UIEvent;
class DELPHICLASS TUIEvent;
__interface DELPHIINTERFACE UIDocumentInteractionControllerClass;
typedef System::DelphiInterface<UIDocumentInteractionControllerClass> _di_UIDocumentInteractionControllerClass;
__interface DELPHIINTERFACE UIDocumentInteractionController;
typedef System::DelphiInterface<UIDocumentInteractionController> _di_UIDocumentInteractionController;
class DELPHICLASS TUIDocumentInteractionController;
__interface DELPHIINTERFACE UITouchClass;
typedef System::DelphiInterface<UITouchClass> _di_UITouchClass;
__interface DELPHIINTERFACE UITouch;
typedef System::DelphiInterface<UITouch> _di_UITouch;
class DELPHICLASS TUITouch;
__interface DELPHIINTERFACE UIColorClass;
typedef System::DelphiInterface<UIColorClass> _di_UIColorClass;
__interface DELPHIINTERFACE UIColor;
typedef System::DelphiInterface<UIColor> _di_UIColor;
class DELPHICLASS TUIColor;
__interface DELPHIINTERFACE UITabBarItemClass;
typedef System::DelphiInterface<UITabBarItemClass> _di_UITabBarItemClass;
__interface DELPHIINTERFACE UITabBarItem;
typedef System::DelphiInterface<UITabBarItem> _di_UITabBarItem;
class DELPHICLASS TUITabBarItem;
__interface DELPHIINTERFACE UIRotationGestureRecognizerClass;
typedef System::DelphiInterface<UIRotationGestureRecognizerClass> _di_UIRotationGestureRecognizerClass;
__interface DELPHIINTERFACE UIRotationGestureRecognizer;
typedef System::DelphiInterface<UIRotationGestureRecognizer> _di_UIRotationGestureRecognizer;
class DELPHICLASS TUIRotationGestureRecognizer;
__interface DELPHIINTERFACE UISwipeGestureRecognizerClass;
typedef System::DelphiInterface<UISwipeGestureRecognizerClass> _di_UISwipeGestureRecognizerClass;
__interface DELPHIINTERFACE UISwipeGestureRecognizer;
typedef System::DelphiInterface<UISwipeGestureRecognizer> _di_UISwipeGestureRecognizer;
class DELPHICLASS TUISwipeGestureRecognizer;
__interface DELPHIINTERFACE UIPinchGestureRecognizerClass;
typedef System::DelphiInterface<UIPinchGestureRecognizerClass> _di_UIPinchGestureRecognizerClass;
__interface DELPHIINTERFACE UIPinchGestureRecognizer;
typedef System::DelphiInterface<UIPinchGestureRecognizer> _di_UIPinchGestureRecognizer;
class DELPHICLASS TUIPinchGestureRecognizer;
__interface DELPHIINTERFACE UIMarkupTextPrintFormatterClass;
typedef System::DelphiInterface<UIMarkupTextPrintFormatterClass> _di_UIMarkupTextPrintFormatterClass;
__interface DELPHIINTERFACE UIMarkupTextPrintFormatter;
typedef System::DelphiInterface<UIMarkupTextPrintFormatter> _di_UIMarkupTextPrintFormatter;
class DELPHICLASS TUIMarkupTextPrintFormatter;
__interface DELPHIINTERFACE UIViewControllerClass;
typedef System::DelphiInterface<UIViewControllerClass> _di_UIViewControllerClass;
__interface DELPHIINTERFACE UIViewController;
typedef System::DelphiInterface<UIViewController> _di_UIViewController;
class DELPHICLASS TUIViewController;
__interface DELPHIINTERFACE UIBarButtonItemClass;
typedef System::DelphiInterface<UIBarButtonItemClass> _di_UIBarButtonItemClass;
__interface DELPHIINTERFACE UIBarButtonItem;
typedef System::DelphiInterface<UIBarButtonItem> _di_UIBarButtonItem;
class DELPHICLASS TUIBarButtonItem;
__interface DELPHIINTERFACE UILongPressGestureRecognizerClass;
typedef System::DelphiInterface<UILongPressGestureRecognizerClass> _di_UILongPressGestureRecognizerClass;
__interface DELPHIINTERFACE UILongPressGestureRecognizer;
typedef System::DelphiInterface<UILongPressGestureRecognizer> _di_UILongPressGestureRecognizer;
class DELPHICLASS TUILongPressGestureRecognizer;
__interface DELPHIINTERFACE UIManagedDocumentClass;
typedef System::DelphiInterface<UIManagedDocumentClass> _di_UIManagedDocumentClass;
__interface DELPHIINTERFACE UIManagedDocument;
typedef System::DelphiInterface<UIManagedDocument> _di_UIManagedDocument;
class DELPHICLASS TUIManagedDocument;
__interface DELPHIINTERFACE UISimpleTextPrintFormatterClass;
typedef System::DelphiInterface<UISimpleTextPrintFormatterClass> _di_UISimpleTextPrintFormatterClass;
__interface DELPHIINTERFACE UISimpleTextPrintFormatter;
typedef System::DelphiInterface<UISimpleTextPrintFormatter> _di_UISimpleTextPrintFormatter;
class DELPHICLASS TUISimpleTextPrintFormatter;
__interface DELPHIINTERFACE UIPanGestureRecognizerClass;
typedef System::DelphiInterface<UIPanGestureRecognizerClass> _di_UIPanGestureRecognizerClass;
__interface DELPHIINTERFACE UIPanGestureRecognizer;
typedef System::DelphiInterface<UIPanGestureRecognizer> _di_UIPanGestureRecognizer;
class DELPHICLASS TUIPanGestureRecognizer;
__interface DELPHIINTERFACE UIStoryboardPopoverSegueClass;
typedef System::DelphiInterface<UIStoryboardPopoverSegueClass> _di_UIStoryboardPopoverSegueClass;
__interface DELPHIINTERFACE UIStoryboardPopoverSegue;
typedef System::DelphiInterface<UIStoryboardPopoverSegue> _di_UIStoryboardPopoverSegue;
class DELPHICLASS TUIStoryboardPopoverSegue;
__interface DELPHIINTERFACE UIApplicationClass;
typedef System::DelphiInterface<UIApplicationClass> _di_UIApplicationClass;
__interface DELPHIINTERFACE UIApplication;
typedef System::DelphiInterface<UIApplication> _di_UIApplication;
class DELPHICLASS TUIApplication;
__interface DELPHIINTERFACE UIViewPrintFormatterClass;
typedef System::DelphiInterface<UIViewPrintFormatterClass> _di_UIViewPrintFormatterClass;
__interface DELPHIINTERFACE UIViewPrintFormatter;
typedef System::DelphiInterface<UIViewPrintFormatter> _di_UIViewPrintFormatter;
class DELPHICLASS TUIViewPrintFormatter;
__interface DELPHIINTERFACE UITapGestureRecognizerClass;
typedef System::DelphiInterface<UITapGestureRecognizerClass> _di_UITapGestureRecognizerClass;
__interface DELPHIINTERFACE UITapGestureRecognizer;
typedef System::DelphiInterface<UITapGestureRecognizer> _di_UITapGestureRecognizer;
class DELPHICLASS TUITapGestureRecognizer;
__interface DELPHIINTERFACE UIWebViewClass;
typedef System::DelphiInterface<UIWebViewClass> _di_UIWebViewClass;
__interface DELPHIINTERFACE UIWebView;
typedef System::DelphiInterface<UIWebView> _di_UIWebView;
class DELPHICLASS TUIWebView;
__interface DELPHIINTERFACE UITableViewControllerClass;
typedef System::DelphiInterface<UITableViewControllerClass> _di_UITableViewControllerClass;
__interface DELPHIINTERFACE UITableViewController;
typedef System::DelphiInterface<UITableViewController> _di_UITableViewController;
class DELPHICLASS TUITableViewController;
__interface DELPHIINTERFACE UIToolbarClass;
typedef System::DelphiInterface<UIToolbarClass> _di_UIToolbarClass;
__interface DELPHIINTERFACE UIToolbar;
typedef System::DelphiInterface<UIToolbar> _di_UIToolbar;
class DELPHICLASS TUIToolbar;
__interface DELPHIINTERFACE UITabBarClass;
typedef System::DelphiInterface<UITabBarClass> _di_UITabBarClass;
__interface DELPHIINTERFACE UITabBar;
typedef System::DelphiInterface<UITabBar> _di_UITabBar;
class DELPHICLASS TUITabBar;
__interface DELPHIINTERFACE UITabBarControllerClass;
typedef System::DelphiInterface<UITabBarControllerClass> _di_UITabBarControllerClass;
__interface DELPHIINTERFACE UITabBarController;
typedef System::DelphiInterface<UITabBarController> _di_UITabBarController;
class DELPHICLASS TUITabBarController;
__interface DELPHIINTERFACE UIWindowClass;
typedef System::DelphiInterface<UIWindowClass> _di_UIWindowClass;
__interface DELPHIINTERFACE UIWindow;
typedef System::DelphiInterface<UIWindow> _di_UIWindow;
class DELPHICLASS TUIWindow;
__interface DELPHIINTERFACE UISplitViewControllerClass;
typedef System::DelphiInterface<UISplitViewControllerClass> _di_UISplitViewControllerClass;
__interface DELPHIINTERFACE UISplitViewController;
typedef System::DelphiInterface<UISplitViewController> _di_UISplitViewController;
class DELPHICLASS TUISplitViewController;
__interface DELPHIINTERFACE UINavigationBarClass;
typedef System::DelphiInterface<UINavigationBarClass> _di_UINavigationBarClass;
__interface DELPHIINTERFACE UINavigationBar;
typedef System::DelphiInterface<UINavigationBar> _di_UINavigationBar;
class DELPHICLASS TUINavigationBar;
__interface DELPHIINTERFACE UILabelClass;
typedef System::DelphiInterface<UILabelClass> _di_UILabelClass;
__interface DELPHIINTERFACE UILabel;
typedef System::DelphiInterface<UILabel> _di_UILabel;
class DELPHICLASS TUILabel;
__interface DELPHIINTERFACE UINavigationControllerClass;
typedef System::DelphiInterface<UINavigationControllerClass> _di_UINavigationControllerClass;
__interface DELPHIINTERFACE UINavigationController;
typedef System::DelphiInterface<UINavigationController> _di_UINavigationController;
class DELPHICLASS TUINavigationController;
__interface DELPHIINTERFACE UIPickerViewClass;
typedef System::DelphiInterface<UIPickerViewClass> _di_UIPickerViewClass;
__interface DELPHIINTERFACE UIPickerView;
typedef System::DelphiInterface<UIPickerView> _di_UIPickerView;
class DELPHICLASS TUIPickerView;
__interface DELPHIINTERFACE UIPageViewControllerClass;
typedef System::DelphiInterface<UIPageViewControllerClass> _di_UIPageViewControllerClass;
__interface DELPHIINTERFACE UIPageViewController;
typedef System::DelphiInterface<UIPageViewController> _di_UIPageViewController;
class DELPHICLASS TUIPageViewController;
__interface DELPHIINTERFACE UIActivityIndicatorViewClass;
typedef System::DelphiInterface<UIActivityIndicatorViewClass> _di_UIActivityIndicatorViewClass;
__interface DELPHIINTERFACE UIActivityIndicatorView;
typedef System::DelphiInterface<UIActivityIndicatorView> _di_UIActivityIndicatorView;
class DELPHICLASS TUIActivityIndicatorView;
__interface DELPHIINTERFACE UIActionSheetClass;
typedef System::DelphiInterface<UIActionSheetClass> _di_UIActionSheetClass;
__interface DELPHIINTERFACE UIActionSheet;
typedef System::DelphiInterface<UIActionSheet> _di_UIActionSheet;
class DELPHICLASS TUIActionSheet;
__interface DELPHIINTERFACE UIActivityViewControllerClass;
typedef System::DelphiInterface<UIActivityViewControllerClass> _di_UIActivityViewControllerClass;
__interface DELPHIINTERFACE UIActivityViewController;
typedef System::DelphiInterface<UIActivityViewController> _di_UIActivityViewController;
class DELPHICLASS TUIActivityViewController;
__interface DELPHIINTERFACE UIAlertViewClass;
typedef System::DelphiInterface<UIAlertViewClass> _di_UIAlertViewClass;
__interface DELPHIINTERFACE UIAlertView;
typedef System::DelphiInterface<UIAlertView> _di_UIAlertView;
class DELPHICLASS TUIAlertView;
__interface DELPHIINTERFACE UIImageViewClass;
typedef System::DelphiInterface<UIImageViewClass> _di_UIImageViewClass;
__interface DELPHIINTERFACE UIImageView;
typedef System::DelphiInterface<UIImageView> _di_UIImageView;
class DELPHICLASS TUIImageView;
__interface DELPHIINTERFACE UIControlClass;
typedef System::DelphiInterface<UIControlClass> _di_UIControlClass;
__interface DELPHIINTERFACE UIControl;
typedef System::DelphiInterface<UIControl> _di_UIControl;
class DELPHICLASS TUIControl;
__interface DELPHIINTERFACE UIProgressViewClass;
typedef System::DelphiInterface<UIProgressViewClass> _di_UIProgressViewClass;
__interface DELPHIINTERFACE UIProgressView;
typedef System::DelphiInterface<UIProgressView> _di_UIProgressView;
class DELPHICLASS TUIProgressView;
__interface DELPHIINTERFACE UIScrollViewClass;
typedef System::DelphiInterface<UIScrollViewClass> _di_UIScrollViewClass;
__interface DELPHIINTERFACE UIScrollView;
typedef System::DelphiInterface<UIScrollView> _di_UIScrollView;
class DELPHICLASS TUIScrollView;
__interface DELPHIINTERFACE UIReferenceLibraryViewControllerClass;
typedef System::DelphiInterface<UIReferenceLibraryViewControllerClass> _di_UIReferenceLibraryViewControllerClass;
__interface DELPHIINTERFACE UIReferenceLibraryViewController;
typedef System::DelphiInterface<UIReferenceLibraryViewController> _di_UIReferenceLibraryViewController;
class DELPHICLASS TUIReferenceLibraryViewController;
__interface DELPHIINTERFACE UIPopoverBackgroundViewClass;
typedef System::DelphiInterface<UIPopoverBackgroundViewClass> _di_UIPopoverBackgroundViewClass;
__interface DELPHIINTERFACE UIPopoverBackgroundView;
typedef System::DelphiInterface<UIPopoverBackgroundView> _di_UIPopoverBackgroundView;
class DELPHICLASS TUIPopoverBackgroundView;
__interface DELPHIINTERFACE UISearchBarClass;
typedef System::DelphiInterface<UISearchBarClass> _di_UISearchBarClass;
__interface DELPHIINTERFACE UISearchBar;
typedef System::DelphiInterface<UISearchBar> _di_UISearchBar;
class DELPHICLASS TUISearchBar;
__interface DELPHIINTERFACE UISearchControllerClass;
typedef System::DelphiInterface<UISearchControllerClass> _di_UISearchControllerClass;
__interface DELPHIINTERFACE UISearchController;
typedef System::DelphiInterface<UISearchController> _di_UISearchController;
class DELPHICLASS TUISearchController;
__interface DELPHIINTERFACE UIVideoEditorControllerClass;
typedef System::DelphiInterface<UIVideoEditorControllerClass> _di_UIVideoEditorControllerClass;
__interface DELPHIINTERFACE UIVideoEditorController;
typedef System::DelphiInterface<UIVideoEditorController> _di_UIVideoEditorController;
class DELPHICLASS TUIVideoEditorController;
__interface DELPHIINTERFACE UIButtonClass;
typedef System::DelphiInterface<UIButtonClass> _di_UIButtonClass;
__interface DELPHIINTERFACE UIButton;
typedef System::DelphiInterface<UIButton> _di_UIButton;
class DELPHICLASS TUIButton;
__interface DELPHIINTERFACE UIStepperClass;
typedef System::DelphiInterface<UIStepperClass> _di_UIStepperClass;
__interface DELPHIINTERFACE UIStepper;
typedef System::DelphiInterface<UIStepper> _di_UIStepper;
class DELPHICLASS TUIStepper;
__interface DELPHIINTERFACE UISliderClass;
typedef System::DelphiInterface<UISliderClass> _di_UISliderClass;
__interface DELPHIINTERFACE UISlider;
typedef System::DelphiInterface<UISlider> _di_UISlider;
class DELPHICLASS TUISlider;
__interface DELPHIINTERFACE UISegmentedControlClass;
typedef System::DelphiInterface<UISegmentedControlClass> _di_UISegmentedControlClass;
__interface DELPHIINTERFACE UISegmentedControl;
typedef System::DelphiInterface<UISegmentedControl> _di_UISegmentedControl;
class DELPHICLASS TUISegmentedControl;
__interface DELPHIINTERFACE UIDatePickerClass;
typedef System::DelphiInterface<UIDatePickerClass> _di_UIDatePickerClass;
__interface DELPHIINTERFACE UIDatePicker;
typedef System::DelphiInterface<UIDatePicker> _di_UIDatePicker;
class DELPHICLASS TUIDatePicker;
__interface DELPHIINTERFACE UIPageControlClass;
typedef System::DelphiInterface<UIPageControlClass> _di_UIPageControlClass;
__interface DELPHIINTERFACE UIPageControl;
typedef System::DelphiInterface<UIPageControl> _di_UIPageControl;
class DELPHICLASS TUIPageControl;
__interface DELPHIINTERFACE UIImagePickerControllerClass;
typedef System::DelphiInterface<UIImagePickerControllerClass> _di_UIImagePickerControllerClass;
__interface DELPHIINTERFACE UIImagePickerController;
typedef System::DelphiInterface<UIImagePickerController> _di_UIImagePickerController;
class DELPHICLASS TUIImagePickerController;
__interface DELPHIINTERFACE UITextViewClass;
typedef System::DelphiInterface<UITextViewClass> _di_UITextViewClass;
__interface DELPHIINTERFACE UITextView;
typedef System::DelphiInterface<UITextView> _di_UITextView;
class DELPHICLASS TUITextView;
__interface DELPHIINTERFACE UISwitchClass;
typedef System::DelphiInterface<UISwitchClass> _di_UISwitchClass;
__interface DELPHIINTERFACE UISwitch;
typedef System::DelphiInterface<UISwitch> _di_UISwitch;
class DELPHICLASS TUISwitch;
__interface DELPHIINTERFACE UIActionSheetDelegate;
typedef System::DelphiInterface<UIActionSheetDelegate> _di_UIActionSheetDelegate;
__interface DELPHIINTERFACE UIAlertViewDelegate;
typedef System::DelphiInterface<UIAlertViewDelegate> _di_UIAlertViewDelegate;
__interface DELPHIINTERFACE UIApplicationDelegate;
typedef System::DelphiInterface<UIApplicationDelegate> _di_UIApplicationDelegate;
__interface DELPHIINTERFACE UIGestureRecognizerDelegate;
typedef System::DelphiInterface<UIGestureRecognizerDelegate> _di_UIGestureRecognizerDelegate;
__interface DELPHIINTERFACE UIImagePickerControllerDelegate;
typedef System::DelphiInterface<UIImagePickerControllerDelegate> _di_UIImagePickerControllerDelegate;
__interface DELPHIINTERFACE UIPickerViewDataSource;
typedef System::DelphiInterface<UIPickerViewDataSource> _di_UIPickerViewDataSource;
__interface DELPHIINTERFACE UIPickerViewDelegate;
typedef System::DelphiInterface<UIPickerViewDelegate> _di_UIPickerViewDelegate;
__interface DELPHIINTERFACE UIPopoverControllerDelegate;
typedef System::DelphiInterface<UIPopoverControllerDelegate> _di_UIPopoverControllerDelegate;
__interface DELPHIINTERFACE UITextSelecting;
typedef System::DelphiInterface<UITextSelecting> _di_UITextSelecting;
__interface DELPHIINTERFACE UITextFieldDelegate;
typedef System::DelphiInterface<UITextFieldDelegate> _di_UITextFieldDelegate;
__interface DELPHIINTERFACE UITextInputTraits;
typedef System::DelphiInterface<UITextInputTraits> _di_UITextInputTraits;
__interface DELPHIINTERFACE UIKeyInput;
typedef System::DelphiInterface<UIKeyInput> _di_UIKeyInput;
__interface DELPHIINTERFACE UITextInput;
typedef System::DelphiInterface<UITextInput> _di_UITextInput;
__interface DELPHIINTERFACE UIWebViewDelegate;
typedef System::DelphiInterface<UIWebViewDelegate> _di_UIWebViewDelegate;
__interface DELPHIINTERFACE UIMotionEffectClass;
typedef System::DelphiInterface<UIMotionEffectClass> _di_UIMotionEffectClass;
__interface DELPHIINTERFACE UIMotionEffect;
typedef System::DelphiInterface<UIMotionEffect> _di_UIMotionEffect;
class DELPHICLASS TUIMotionEffect;
__interface DELPHIINTERFACE UITextFieldClass;
typedef System::DelphiInterface<UITextFieldClass> _di_UITextFieldClass;
__interface DELPHIINTERFACE UITextField;
typedef System::DelphiInterface<UITextField> _di_UITextField;
class DELPHICLASS TUITextField;
__interface DELPHIINTERFACE UITableViewClass;
typedef System::DelphiInterface<UITableViewClass> _di_UITableViewClass;
__interface DELPHIINTERFACE UITableView;
typedef System::DelphiInterface<UITableView> _di_UITableView;
class DELPHICLASS TUITableView;
__interface DELPHIINTERFACE UITableViewCellClass;
typedef System::DelphiInterface<UITableViewCellClass> _di_UITableViewCellClass;
__interface DELPHIINTERFACE UITableViewCell;
typedef System::DelphiInterface<UITableViewCell> _di_UITableViewCell;
class DELPHICLASS TUITableViewCell;
__interface DELPHIINTERFACE UITableViewHeaderFooterViewClass;
typedef System::DelphiInterface<UITableViewHeaderFooterViewClass> _di_UITableViewHeaderFooterViewClass;
__interface DELPHIINTERFACE UITableViewHeaderFooterView;
typedef System::DelphiInterface<UITableViewHeaderFooterView> _di_UITableViewHeaderFooterView;
class DELPHICLASS TUITableViewHeaderFooterView;
__interface DELPHIINTERFACE UIRefreshControlClass;
typedef System::DelphiInterface<UIRefreshControlClass> _di_UIRefreshControlClass;
__interface DELPHIINTERFACE UIRefreshControl;
typedef System::DelphiInterface<UIRefreshControl> _di_UIRefreshControl;
class DELPHICLASS TUIRefreshControl;
__interface DELPHIINTERFACE NSValueClass;
typedef System::DelphiInterface<NSValueClass> _di_NSValueClass;
__interface DELPHIINTERFACE NSValue;
typedef System::DelphiInterface<NSValue> _di_NSValue;
class DELPHICLASS TNSValue;
__interface DELPHIINTERFACE UITextPositionClass;
typedef System::DelphiInterface<UITextPositionClass> _di_UITextPositionClass;
__interface DELPHIINTERFACE UITextPosition;
typedef System::DelphiInterface<UITextPosition> _di_UITextPosition;
class DELPHICLASS TUITextPosition;
__interface DELPHIINTERFACE UITextSelectionRectClass;
typedef System::DelphiInterface<UITextSelectionRectClass> _di_UITextSelectionRectClass;
__interface DELPHIINTERFACE UITextSelectionRect;
typedef System::DelphiInterface<UITextSelectionRect> _di_UITextSelectionRect;
class DELPHICLASS TUITextSelectionRect;
__interface DELPHIINTERFACE UIDictationPhraseClass;
typedef System::DelphiInterface<UIDictationPhraseClass> _di_UIDictationPhraseClass;
__interface DELPHIINTERFACE UIDictationPhrase;
typedef System::DelphiInterface<UIDictationPhrase> _di_UIDictationPhrase;
class DELPHICLASS TUIDictationPhrase;
__interface DELPHIINTERFACE UIActivityClass;
typedef System::DelphiInterface<UIActivityClass> _di_UIActivityClass;
__interface DELPHIINTERFACE UIActivity;
typedef System::DelphiInterface<UIActivity> _di_UIActivity;
class DELPHICLASS TUIActivity;
__interface DELPHIINTERFACE UIActivityItemProviderClass;
typedef System::DelphiInterface<UIActivityItemProviderClass> _di_UIActivityItemProviderClass;
__interface DELPHIINTERFACE UIActivityItemProvider;
typedef System::DelphiInterface<UIActivityItemProvider> _di_UIActivityItemProvider;
class DELPHICLASS TUIActivityItemProvider;
__interface DELPHIINTERFACE UIAttachmentBehaviorClass;
typedef System::DelphiInterface<UIAttachmentBehaviorClass> _di_UIAttachmentBehaviorClass;
__interface DELPHIINTERFACE UIAttachmentBehavior;
typedef System::DelphiInterface<UIAttachmentBehavior> _di_UIAttachmentBehavior;
class DELPHICLASS TUIAttachmentBehavior;
__interface DELPHIINTERFACE UICollectionViewClass;
typedef System::DelphiInterface<UICollectionViewClass> _di_UICollectionViewClass;
__interface DELPHIINTERFACE UICollectionView;
typedef System::DelphiInterface<UICollectionView> _di_UICollectionView;
class DELPHICLASS TUICollectionView;
__interface DELPHIINTERFACE UICollectionReusableViewClass;
typedef System::DelphiInterface<UICollectionReusableViewClass> _di_UICollectionReusableViewClass;
__interface DELPHIINTERFACE UICollectionReusableView;
typedef System::DelphiInterface<UICollectionReusableView> _di_UICollectionReusableView;
class DELPHICLASS TUICollectionReusableView;
__interface DELPHIINTERFACE UICollectionViewCellClass;
typedef System::DelphiInterface<UICollectionViewCellClass> _di_UICollectionViewCellClass;
__interface DELPHIINTERFACE UICollectionViewCell;
typedef System::DelphiInterface<UICollectionViewCell> _di_UICollectionViewCell;
class DELPHICLASS TUICollectionViewCell;
__interface DELPHIINTERFACE UICollectionViewLayoutClass;
typedef System::DelphiInterface<UICollectionViewLayoutClass> _di_UICollectionViewLayoutClass;
__interface DELPHIINTERFACE UICollectionViewLayout;
typedef System::DelphiInterface<UICollectionViewLayout> _di_UICollectionViewLayout;
class DELPHICLASS TUICollectionViewLayout;
__interface DELPHIINTERFACE UICollectionViewTransitionLayoutClass;
typedef System::DelphiInterface<UICollectionViewTransitionLayoutClass> _di_UICollectionViewTransitionLayoutClass;
__interface DELPHIINTERFACE UICollectionViewTransitionLayout;
typedef System::DelphiInterface<UICollectionViewTransitionLayout> _di_UICollectionViewTransitionLayout;
class DELPHICLASS TUICollectionViewTransitionLayout;
__interface DELPHIINTERFACE UICollectionViewLayoutAttributesClass;
typedef System::DelphiInterface<UICollectionViewLayoutAttributesClass> _di_UICollectionViewLayoutAttributesClass;
__interface DELPHIINTERFACE UICollectionViewLayoutAttributes;
typedef System::DelphiInterface<UICollectionViewLayoutAttributes> _di_UICollectionViewLayoutAttributes;
class DELPHICLASS TUICollectionViewLayoutAttributes;
__interface DELPHIINTERFACE UICollectionViewControllerClass;
typedef System::DelphiInterface<UICollectionViewControllerClass> _di_UICollectionViewControllerClass;
__interface DELPHIINTERFACE UICollectionViewController;
typedef System::DelphiInterface<UICollectionViewController> _di_UICollectionViewController;
class DELPHICLASS TUICollectionViewController;
__interface DELPHIINTERFACE UICollectionViewUpdateItemClass;
typedef System::DelphiInterface<UICollectionViewUpdateItemClass> _di_UICollectionViewUpdateItemClass;
__interface DELPHIINTERFACE UICollectionViewUpdateItem;
typedef System::DelphiInterface<UICollectionViewUpdateItem> _di_UICollectionViewUpdateItem;
class DELPHICLASS TUICollectionViewUpdateItem;
__interface DELPHIINTERFACE UICollectionViewLayoutInvalidationContextClass;
typedef System::DelphiInterface<UICollectionViewLayoutInvalidationContextClass> _di_UICollectionViewLayoutInvalidationContextClass;
__interface DELPHIINTERFACE UICollectionViewLayoutInvalidationContext;
typedef System::DelphiInterface<UICollectionViewLayoutInvalidationContext> _di_UICollectionViewLayoutInvalidationContext;
class DELPHICLASS TUICollectionViewLayoutInvalidationContext;
__interface DELPHIINTERFACE UICollectionViewFlowLayoutInvalidationContextClass;
typedef System::DelphiInterface<UICollectionViewFlowLayoutInvalidationContextClass> _di_UICollectionViewFlowLayoutInvalidationContextClass;
__interface DELPHIINTERFACE UICollectionViewFlowLayoutInvalidationContext;
typedef System::DelphiInterface<UICollectionViewFlowLayoutInvalidationContext> _di_UICollectionViewFlowLayoutInvalidationContext;
class DELPHICLASS TUICollectionViewFlowLayoutInvalidationContext;
__interface DELPHIINTERFACE UICollectionViewFlowLayoutClass;
typedef System::DelphiInterface<UICollectionViewFlowLayoutClass> _di_UICollectionViewFlowLayoutClass;
__interface DELPHIINTERFACE UICollectionViewFlowLayout;
typedef System::DelphiInterface<UICollectionViewFlowLayout> _di_UICollectionViewFlowLayout;
class DELPHICLASS TUICollectionViewFlowLayout;
__interface DELPHIINTERFACE UIInputViewClass;
typedef System::DelphiInterface<UIInputViewClass> _di_UIInputViewClass;
__interface DELPHIINTERFACE UIInputView;
typedef System::DelphiInterface<UIInputView> _di_UIInputView;
class DELPHICLASS TUIInputView;
__interface DELPHIINTERFACE UIInterpolatingMotionEffectClass;
typedef System::DelphiInterface<UIInterpolatingMotionEffectClass> _di_UIInterpolatingMotionEffectClass;
__interface DELPHIINTERFACE UIInterpolatingMotionEffect;
typedef System::DelphiInterface<UIInterpolatingMotionEffect> _di_UIInterpolatingMotionEffect;
class DELPHICLASS TUIInterpolatingMotionEffect;
__interface DELPHIINTERFACE UIMotionEffectGroupClass;
typedef System::DelphiInterface<UIMotionEffectGroupClass> _di_UIMotionEffectGroupClass;
__interface DELPHIINTERFACE UIMotionEffectGroup;
typedef System::DelphiInterface<UIMotionEffectGroup> _di_UIMotionEffectGroup;
class DELPHICLASS TUIMotionEffectGroup;
__interface DELPHIINTERFACE UIScreenEdgePanGestureRecognizerClass;
typedef System::DelphiInterface<UIScreenEdgePanGestureRecognizerClass> _di_UIScreenEdgePanGestureRecognizerClass;
__interface DELPHIINTERFACE UIScreenEdgePanGestureRecognizer;
typedef System::DelphiInterface<UIScreenEdgePanGestureRecognizer> _di_UIScreenEdgePanGestureRecognizer;
class DELPHICLASS TUIScreenEdgePanGestureRecognizer;
__interface DELPHIINTERFACE UIPercentDrivenInteractiveTransitionClass;
typedef System::DelphiInterface<UIPercentDrivenInteractiveTransitionClass> _di_UIPercentDrivenInteractiveTransitionClass;
__interface DELPHIINTERFACE UIPercentDrivenInteractiveTransition;
typedef System::DelphiInterface<UIPercentDrivenInteractiveTransition> _di_UIPercentDrivenInteractiveTransition;
class DELPHICLASS TUIPercentDrivenInteractiveTransition;
__interface DELPHIINTERFACE UIPushBehaviorClass;
typedef System::DelphiInterface<UIPushBehaviorClass> _di_UIPushBehaviorClass;
__interface DELPHIINTERFACE UIPushBehavior;
typedef System::DelphiInterface<UIPushBehavior> _di_UIPushBehavior;
class DELPHICLASS TUIPushBehavior;
__interface DELPHIINTERFACE UISnapBehaviorClass;
typedef System::DelphiInterface<UISnapBehaviorClass> _di_UISnapBehaviorClass;
__interface DELPHIINTERFACE UISnapBehavior;
typedef System::DelphiInterface<UISnapBehavior> _di_UISnapBehavior;
class DELPHICLASS TUISnapBehavior;
__interface DELPHIINTERFACE UIDynamicItemBehaviorClass;
typedef System::DelphiInterface<UIDynamicItemBehaviorClass> _di_UIDynamicItemBehaviorClass;
__interface DELPHIINTERFACE UIDynamicItemBehavior;
typedef System::DelphiInterface<UIDynamicItemBehavior> _di_UIDynamicItemBehavior;
class DELPHICLASS TUIDynamicItemBehavior;
__interface DELPHIINTERFACE UIGravityBehaviorClass;
typedef System::DelphiInterface<UIGravityBehaviorClass> _di_UIGravityBehaviorClass;
__interface DELPHIINTERFACE UIGravityBehavior;
typedef System::DelphiInterface<UIGravityBehavior> _di_UIGravityBehavior;
class DELPHICLASS TUIGravityBehavior;
__interface DELPHIINTERFACE UICollisionBehaviorClass;
typedef System::DelphiInterface<UICollisionBehaviorClass> _di_UICollisionBehaviorClass;
__interface DELPHIINTERFACE UICollisionBehavior;
typedef System::DelphiInterface<UICollisionBehavior> _di_UICollisionBehavior;
class DELPHICLASS TUICollisionBehavior;
__interface DELPHIINTERFACE UILayoutSupport;
typedef System::DelphiInterface<UILayoutSupport> _di_UILayoutSupport;
__interface DELPHIINTERFACE NSTextStorageDelegate;
typedef System::DelphiInterface<NSTextStorageDelegate> _di_NSTextStorageDelegate;
__interface DELPHIINTERFACE NSLayoutManagerDelegate;
typedef System::DelphiInterface<NSLayoutManagerDelegate> _di_NSLayoutManagerDelegate;
__interface DELPHIINTERFACE NSTextLayoutOrientationProvider;
typedef System::DelphiInterface<NSTextLayoutOrientationProvider> _di_NSTextLayoutOrientationProvider;
__interface DELPHIINTERFACE NSTextAttachmentContainer;
typedef System::DelphiInterface<NSTextAttachmentContainer> _di_NSTextAttachmentContainer;
__interface DELPHIINTERFACE UIAccelerometerDelegate;
typedef System::DelphiInterface<UIAccelerometerDelegate> _di_UIAccelerometerDelegate;
__interface DELPHIINTERFACE UIAppearanceContainer;
typedef System::DelphiInterface<UIAppearanceContainer> _di_UIAppearanceContainer;
__interface DELPHIINTERFACE UIAppearance;
typedef System::DelphiInterface<UIAppearance> _di_UIAppearance;
__interface DELPHIINTERFACE UIDynamicItem;
typedef System::DelphiInterface<UIDynamicItem> _di_UIDynamicItem;
__interface DELPHIINTERFACE UIScrollViewDelegate;
typedef System::DelphiInterface<UIScrollViewDelegate> _di_UIScrollViewDelegate;
__interface DELPHIINTERFACE UITableViewDataSource;
typedef System::DelphiInterface<UITableViewDataSource> _di_UITableViewDataSource;
__interface DELPHIINTERFACE UITableViewDelegate;
typedef System::DelphiInterface<UITableViewDelegate> _di_UITableViewDelegate;
__interface DELPHIINTERFACE UIPickerViewAccessibilityDelegate;
typedef System::DelphiInterface<UIPickerViewAccessibilityDelegate> _di_UIPickerViewAccessibilityDelegate;
__interface DELPHIINTERFACE UIScrollViewAccessibilityDelegate;
typedef System::DelphiInterface<UIScrollViewAccessibilityDelegate> _di_UIScrollViewAccessibilityDelegate;
__interface DELPHIINTERFACE UIAccessibilityIdentification;
typedef System::DelphiInterface<UIAccessibilityIdentification> _di_UIAccessibilityIdentification;
__interface DELPHIINTERFACE UIGuidedAccessRestrictionDelegate;
typedef System::DelphiInterface<UIGuidedAccessRestrictionDelegate> _di_UIGuidedAccessRestrictionDelegate;
__interface DELPHIINTERFACE UIAccessibilityReadingContent;
typedef System::DelphiInterface<UIAccessibilityReadingContent> _di_UIAccessibilityReadingContent;
__interface DELPHIINTERFACE UITextInputTokenizer;
typedef System::DelphiInterface<UITextInputTokenizer> _di_UITextInputTokenizer;
__interface DELPHIINTERFACE UITextInputDelegate;
typedef System::DelphiInterface<UITextInputDelegate> _di_UITextInputDelegate;
__interface DELPHIINTERFACE UIActivityItemSource;
typedef System::DelphiInterface<UIActivityItemSource> _di_UIActivityItemSource;
__interface DELPHIINTERFACE UIInputViewAudioFeedback;
typedef System::DelphiInterface<UIInputViewAudioFeedback> _di_UIInputViewAudioFeedback;
__interface DELPHIINTERFACE UIStateRestoring;
typedef System::DelphiInterface<UIStateRestoring> _di_UIStateRestoring;
__interface DELPHIINTERFACE UIViewControllerRestoration;
typedef System::DelphiInterface<UIViewControllerRestoration> _di_UIViewControllerRestoration;
__interface DELPHIINTERFACE UIDataSourceModelAssociation;
typedef System::DelphiInterface<UIDataSourceModelAssociation> _di_UIDataSourceModelAssociation;
__interface DELPHIINTERFACE UIObjectRestoration;
typedef System::DelphiInterface<UIObjectRestoration> _di_UIObjectRestoration;
__interface DELPHIINTERFACE UIViewControllerTransitioningDelegate;
typedef System::DelphiInterface<UIViewControllerTransitioningDelegate> _di_UIViewControllerTransitioningDelegate;
__interface DELPHIINTERFACE UIBarPositioning;
typedef System::DelphiInterface<UIBarPositioning> _di_UIBarPositioning;
__interface DELPHIINTERFACE UIBarPositioningDelegate;
typedef System::DelphiInterface<UIBarPositioningDelegate> _di_UIBarPositioningDelegate;
__interface DELPHIINTERFACE UICollectionViewDataSource;
typedef System::DelphiInterface<UICollectionViewDataSource> _di_UICollectionViewDataSource;
__interface DELPHIINTERFACE UICollectionViewDelegate;
typedef System::DelphiInterface<UICollectionViewDelegate> _di_UICollectionViewDelegate;
__interface DELPHIINTERFACE UICollectionViewDelegateFlowLayout;
typedef System::DelphiInterface<UICollectionViewDelegateFlowLayout> _di_UICollectionViewDelegateFlowLayout;
__interface DELPHIINTERFACE UIDocumentInteractionControllerDelegate;
typedef System::DelphiInterface<UIDocumentInteractionControllerDelegate> _di_UIDocumentInteractionControllerDelegate;
__interface DELPHIINTERFACE UINavigationControllerDelegate;
typedef System::DelphiInterface<UINavigationControllerDelegate> _di_UINavigationControllerDelegate;
__interface DELPHIINTERFACE UIViewControllerInteractiveTransitioning;
typedef System::DelphiInterface<UIViewControllerInteractiveTransitioning> _di_UIViewControllerInteractiveTransitioning;
__interface DELPHIINTERFACE UIViewControllerAnimatedTransitioning;
typedef System::DelphiInterface<UIViewControllerAnimatedTransitioning> _di_UIViewControllerAnimatedTransitioning;
__interface DELPHIINTERFACE UINavigationBarDelegate;
typedef System::DelphiInterface<UINavigationBarDelegate> _di_UINavigationBarDelegate;
__interface DELPHIINTERFACE UIPageViewControllerDelegate;
typedef System::DelphiInterface<UIPageViewControllerDelegate> _di_UIPageViewControllerDelegate;
__interface DELPHIINTERFACE UIPageViewControllerDataSource;
typedef System::DelphiInterface<UIPageViewControllerDataSource> _di_UIPageViewControllerDataSource;
__interface DELPHIINTERFACE UIPrintInteractionControllerDelegate;
typedef System::DelphiInterface<UIPrintInteractionControllerDelegate> _di_UIPrintInteractionControllerDelegate;
__interface DELPHIINTERFACE UISearchBarDelegate;
typedef System::DelphiInterface<UISearchBarDelegate> _di_UISearchBarDelegate;
__interface DELPHIINTERFACE UISearchDisplayDelegate;
typedef System::DelphiInterface<UISearchDisplayDelegate> _di_UISearchDisplayDelegate;
__interface DELPHIINTERFACE UISplitViewControllerDelegate;
typedef System::DelphiInterface<UISplitViewControllerDelegate> _di_UISplitViewControllerDelegate;
__interface DELPHIINTERFACE UITabBarDelegate;
typedef System::DelphiInterface<UITabBarDelegate> _di_UITabBarDelegate;
__interface DELPHIINTERFACE UIViewControllerTransitionCoordinatorContext;
typedef System::DelphiInterface<UIViewControllerTransitionCoordinatorContext> _di_UIViewControllerTransitionCoordinatorContext;
__interface DELPHIINTERFACE UIViewControllerTransitionCoordinator;
typedef System::DelphiInterface<UIViewControllerTransitionCoordinator> _di_UIViewControllerTransitionCoordinator;
__interface DELPHIINTERFACE UIViewControllerContextTransitioning;
typedef System::DelphiInterface<UIViewControllerContextTransitioning> _di_UIViewControllerContextTransitioning;
__interface DELPHIINTERFACE UITabBarControllerDelegate;
typedef System::DelphiInterface<UITabBarControllerDelegate> _di_UITabBarControllerDelegate;
__interface DELPHIINTERFACE UITextViewDelegate;
typedef System::DelphiInterface<UITextViewDelegate> _di_UITextViewDelegate;
__interface DELPHIINTERFACE UIToolbarDelegate;
typedef System::DelphiInterface<UIToolbarDelegate> _di_UIToolbarDelegate;
__interface DELPHIINTERFACE UIVideoEditorControllerDelegate;
typedef System::DelphiInterface<UIVideoEditorControllerDelegate> _di_UIVideoEditorControllerDelegate;
__interface DELPHIINTERFACE UIDynamicAnimatorDelegate;
typedef System::DelphiInterface<UIDynamicAnimatorDelegate> _di_UIDynamicAnimatorDelegate;
__interface DELPHIINTERFACE UICollisionBehaviorDelegate;
typedef System::DelphiInterface<UICollisionBehaviorDelegate> _di_UICollisionBehaviorDelegate;
__interface DELPHIINTERFACE UIContentContainer;
typedef System::DelphiInterface<UIContentContainer> _di_UIContentContainer;
__interface DELPHIINTERFACE UITextDocumentProxy;
typedef System::DelphiInterface<UITextDocumentProxy> _di_UITextDocumentProxy;
__interface DELPHIINTERFACE UIPopoverBackgroundViewMethods;
typedef System::DelphiInterface<UIPopoverBackgroundViewMethods> _di_UIPopoverBackgroundViewMethods;
__interface DELPHIINTERFACE UIPrinterPickerControllerDelegate;
typedef System::DelphiInterface<UIPrinterPickerControllerDelegate> _di_UIPrinterPickerControllerDelegate;
__interface DELPHIINTERFACE UIAdaptivePresentationControllerDelegate;
typedef System::DelphiInterface<UIAdaptivePresentationControllerDelegate> _di_UIAdaptivePresentationControllerDelegate;
__interface DELPHIINTERFACE UISearchControllerDelegate;
typedef System::DelphiInterface<UISearchControllerDelegate> _di_UISearchControllerDelegate;
__interface DELPHIINTERFACE UISearchResultsUpdating;
typedef System::DelphiInterface<UISearchResultsUpdating> _di_UISearchResultsUpdating;
__interface DELPHIINTERFACE UIPopoverPresentationControllerDelegate;
typedef System::DelphiInterface<UIPopoverPresentationControllerDelegate> _di_UIPopoverPresentationControllerDelegate;
__interface DELPHIINTERFACE UIContextMenuConfigurationClass;
typedef System::DelphiInterface<UIContextMenuConfigurationClass> _di_UIContextMenuConfigurationClass;
__interface DELPHIINTERFACE UIContextMenuConfiguration;
typedef System::DelphiInterface<UIContextMenuConfiguration> _di_UIContextMenuConfiguration;
class DELPHICLASS TUIContextMenuConfiguration;
__interface DELPHIINTERFACE UIMenuElementClass;
typedef System::DelphiInterface<UIMenuElementClass> _di_UIMenuElementClass;
__interface DELPHIINTERFACE UIMenuElement;
typedef System::DelphiInterface<UIMenuElement> _di_UIMenuElement;
class DELPHICLASS TUIMenuElement;
__interface DELPHIINTERFACE UIMenuClass;
typedef System::DelphiInterface<UIMenuClass> _di_UIMenuClass;
__interface DELPHIINTERFACE UIMenu;
typedef System::DelphiInterface<UIMenu> _di_UIMenu;
class DELPHICLASS TUIMenu;
__interface DELPHIINTERFACE UIAlertActionClass;
typedef System::DelphiInterface<UIAlertActionClass> _di_UIAlertActionClass;
__interface DELPHIINTERFACE UIAlertAction;
typedef System::DelphiInterface<UIAlertAction> _di_UIAlertAction;
class DELPHICLASS TUIAlertAction;
__interface DELPHIINTERFACE UIAlertControllerClass;
typedef System::DelphiInterface<UIAlertControllerClass> _di_UIAlertControllerClass;
__interface DELPHIINTERFACE UIAlertController;
typedef System::DelphiInterface<UIAlertController> _di_UIAlertController;
class DELPHICLASS TUIAlertController;
//-- type declarations -------------------------------------------------------
typedef void * PUIImage;

typedef void * PNSData;

typedef long NSUnderlineStyle;

typedef long NSTextWritingDirection;

struct DECLSPEC_DRECORD UIEdgeInsets
{
public:
	double top;
	double left;
	double bottom;
	double right;
};


typedef UIEdgeInsets *PUIEdgeInsets;

struct DECLSPEC_DRECORD UIOffset
{
public:
	double horizontal;
	double vertical;
};


typedef UIOffset *PUIOffset;

typedef void * PUIApplication;

typedef unsigned long UIRectEdge;

typedef long NSLayoutRelation;

typedef long NSLayoutAttribute;

typedef unsigned long NSLayoutFormatOptions;

typedef float UILayoutPriority;

typedef unsigned long NSTextStorageEditActions;

typedef unsigned UIFontDescriptorSymbolicTraits;

typedef unsigned long _UIFontDescriptorClass;

typedef long NSTextLayoutOrientation;

typedef long NSGlyphProperty;

typedef long NSControlCharacterAction;

typedef void __fastcall (__closure *TUIKitUsingBlock)(const Iosapi::Foundation::NSRect &param1, const Iosapi::Foundation::NSRect &param2, _di_NSTextContainer param3, const Iosapi::Foundation::NSRange &param4, bool param5);

typedef void __fastcall (__closure *TUIKitUsingBlock1)(const Iosapi::Foundation::NSRect &param1, bool param2);

typedef long NSTextAlignment;

typedef long NSWritingDirection;

typedef long NSLineBreakMode;

typedef long NSStringDrawingOptions;

typedef double UIAccelerationValue;

typedef unsigned long UIRectCorner;

typedef long UIEventType;

typedef long UIEventSubtype;

typedef long UIKeyModifierFlags;

typedef long UIBarStyle;

typedef long UIUserInterfaceStyle;

typedef void __fastcall (__closure *TUIKitAction)(void);

typedef long UIViewAnimationCurve;

typedef long UIViewContentMode;

typedef long UIViewAnimationTransition;

typedef unsigned long UIViewAutoresizing;

typedef unsigned long UIViewAnimationOptions;

typedef unsigned long UIViewKeyframeAnimationOptions;

typedef unsigned long UISystemAnimation;

typedef long UIViewTintAdjustmentMode;

typedef void __fastcall (__closure *TUIKitCompletion)(bool param1);

typedef long UILayoutConstraintAxis;

typedef long UIScrollViewIndicatorStyle;

typedef long UIScrollViewKeyboardDismissMode;

typedef long UIGestureRecognizerState;

typedef unsigned long UISwipeGestureRecognizerDirection;

typedef long UILineBreakMode;

typedef long UITextAlignment;

typedef long UIBaselineAdjustment;

typedef long UITableViewCellStyle;

typedef long UITableViewCellSeparatorStyle;

typedef long UITableViewCellSelectionStyle;

typedef long UITableViewCellEditingStyle;

typedef long UITableViewCellAccessoryType;

typedef unsigned long UITableViewCellStateMask;

typedef long UITableViewStyle;

typedef long UITableViewScrollPosition;

typedef long UITableViewRowAnimation;

typedef unsigned __int64 UIAccessibilityTraits;

typedef unsigned UIAccessibilityNotifications;

typedef long UIImageOrientation;

typedef long UIImageResizingMode;

typedef long UIImageRenderingMode;

typedef long UIAccessibilityZoomType;

typedef long UIGuidedAccessRestrictionState;

typedef long UIAccessibilityScrollDirection;

typedef unsigned long UIControlEvents;

typedef long UIControlContentVerticalAlignment;

typedef long UIControlContentHorizontalAlignment;

typedef unsigned long UIControlState;

typedef long UITextAutocapitalizationType;

typedef long UITextAutocorrectionType;

typedef long UITextSpellCheckingType;

typedef long UIKeyboardType;

typedef long UIKeyboardAppearance;

typedef long UIReturnKeyType;

typedef long UITextStorageDirection;

typedef long UITextLayoutDirection;

typedef long UITextDirection;

typedef long UITextWritingDirection;

typedef unsigned long UIToolbarPosition;

typedef long UITextGranularity;

typedef long UITextBorderStyle;

typedef long UITextFieldViewMode;

typedef long UIActionSheetStyle;

typedef long UIActivityCategory;

typedef long UIActivityIndicatorViewStyle;

typedef long UIDeviceOrientation;

typedef long UIDeviceBatteryState;

typedef long UIUserInterfaceIdiom;

typedef long UIAlertViewStyle;

typedef long UIStatusBarStyle;

typedef long UIStatusBarAnimation;

typedef long UIInterfaceOrientation;

typedef unsigned long UIInterfaceOrientationMask;

typedef unsigned long UIRemoteNotificationType;

typedef unsigned long UIBackgroundFetchResult;

typedef long UIBackgroundRefreshStatus;

typedef long UIApplicationState;

typedef unsigned long UIBackgroundTaskIdentifier;

typedef long UIUserInterfaceLayoutDirection;

typedef void __fastcall (__closure *TUIKitCompletionHandler)(unsigned long param1);

typedef long UIModalTransitionStyle;

typedef long UIModalPresentationStyle;

typedef void __fastcall (__closure *UIActivityViewControllerCompletionHandler)(Iosapi::Foundation::_di_NSString param1, bool param2);

typedef long UIAttachmentBehaviorType;

typedef long UIBarMetrics;

typedef long UIBarPosition;

typedef long UIBarButtonItemStyle;

typedef long UIBarButtonSystemItem;

typedef long UIButtonType;

typedef unsigned long UICollectionViewScrollPosition;

typedef void __fastcall (__closure *UICollectionViewLayoutInteractiveTransitionCompletion)(bool param1, bool param2);

typedef unsigned long UICollectionElementCategory;

typedef long UICollectionUpdateAction;

typedef long UICollectionViewScrollDirection;

typedef unsigned long UIDataDetectorTypes;

typedef long UIDatePickerMode;

typedef long UIDocumentChangeKind;

typedef long UIDocumentSaveOperation;

typedef unsigned long UIDocumentState;

typedef long UINavigationControllerOperation;

typedef long UIImagePickerControllerSourceType;

typedef long UIImagePickerControllerQualityType;

typedef long UIImagePickerControllerCameraCaptureMode;

typedef long UIImagePickerControllerCameraDevice;

typedef long UIImagePickerControllerCameraFlashMode;

typedef long UIInputViewStyle;

typedef long UIMenuControllerArrowDirection;

typedef long UIInterpolatingMotionEffectType;

typedef long UIPageViewControllerNavigationOrientation;

typedef long UIPageViewControllerSpineLocation;

typedef long UIPageViewControllerNavigationDirection;

typedef long UIPageViewControllerTransitionStyle;

typedef unsigned long UIPopoverArrowDirection;

typedef long UIPrintInfoOutputType;

typedef long UIPrintInfoOrientation;

typedef long UIPrintInfoDuplex;

typedef void __fastcall (__closure *UIPrintInteractionCompletionHandler)(_di_UIPrintInteractionController param1, bool param2, Iosapi::Foundation::_di_NSError param3);

typedef long UIProgressViewStyle;

typedef long UIScreenOverscanCompensation;

typedef long UISearchBarIcon;

typedef unsigned long UISearchBarStyle;

typedef long UISegmentedControlStyle;

typedef long UISegmentedControlSegment;

typedef long UITabBarItemPositioning;

typedef void __fastcall (__closure *TUIKitAnimation)(void * param1);

typedef long UITabBarSystemItem;

typedef long UITouchPhase;

typedef long UIWebViewNavigationType;

typedef long UIWebPaginationMode;

typedef long UIWebPaginationBreakingMode;

typedef double UIWindowLevel;

typedef long UIPushBehaviorMode;

typedef unsigned long UICollisionBehaviorMode;

typedef unsigned long UIUserNotificationType;

typedef void __fastcall (__closure *UIPrinterPickerCompletionHandler)(_di_UIPrinterPickerController param1, bool param2, Iosapi::Foundation::_di_NSError param3);

typedef Iosapi::Foundation::_di_NSString UIMenuIdentifier;

typedef long UIMenuOptions;

typedef Iosapi::Foundation::_di_NSString NSAttributedStringDocumentReadingOptionKey;

typedef _di_UIViewController __fastcall (__closure *UIContextMenuContentPreviewProvider)(void);

typedef _di_UIMenu __fastcall (__closure *UIContextMenuActionProvider)(Iosapi::Foundation::_di_NSArray suggestedActions);

typedef Iosapi::Foundation::_di_NSString UIContentSizeCategory;

typedef long UIAlertActionStyle;

typedef long UIAlertControllerStyle;

typedef void __fastcall (__closure *TUIKitHandler)(_di_UIAlertAction action);

typedef void __fastcall (__closure *TUIKitConfigurationHandler)(_di_UITextField textField);

__interface  INTERFACE_UUID("{87A9BD00-B352-4FF7-BF16-6131B4CD6DC0}") NSLayoutConstraintClass  : public Iosapi::Quartzcore::NSObjectClass 
{
	virtual Iosapi::Foundation::_di_NSArray __cdecl constraintsWithVisualFormat(Iosapi::Foundation::_di_NSString format, unsigned long opts, Iosapi::Foundation::_di_NSDictionary metrics, Iosapi::Foundation::_di_NSDictionary views) = 0 ;
	virtual void * __cdecl constraintWithItem(void * view1, long attr1, long relation, void * view2, long attr2, double multiplier, double c) = 0 ;
	virtual void __cdecl activateConstraints(Iosapi::Foundation::_di_NSArray constraints) = 0 ;
	virtual void __cdecl deactivateConstraints(Iosapi::Foundation::_di_NSArray constraints) = 0 ;
};

__interface  INTERFACE_UUID("{C182C818-64BB-480C-A0DA-EF97164A4A86}") NSLayoutConstraint  : public Iosapi::Foundation::NSObject 
{
	virtual void __cdecl setPriority(float priority) = 0 ;
	virtual float __cdecl priority() = 0 ;
	virtual void __cdecl setShouldBeArchived(bool shouldBeArchived) = 0 ;
	virtual bool __cdecl shouldBeArchived() = 0 ;
	virtual void * __cdecl firstItem() = 0 ;
	virtual long __cdecl firstAttribute() = 0 ;
	virtual long __cdecl relation() = 0 ;
	virtual void * __cdecl secondItem() = 0 ;
	virtual long __cdecl secondAttribute() = 0 ;
	virtual double __cdecl multiplier() = 0 ;
	virtual void __cdecl setConstant(double constant) = 0 ;
	virtual double __cdecl constant() = 0 ;
	virtual void __cdecl setActive(bool active) = 0 ;
	virtual bool __cdecl isActive() = 0 ;
	virtual void __cdecl setIdentifier(Iosapi::Foundation::_di_NSString identifier) = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl identifier() = 0 ;
};

class PASCALIMPLEMENTATION TNSLayoutConstraint : public Macapi::Objectivec::TOCGenericImport__2<_di_NSLayoutConstraintClass,_di_NSLayoutConstraint>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSLayoutConstraintClass,_di_NSLayoutConstraint> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSLayoutConstraint(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSLayoutConstraintClass,_di_NSLayoutConstraint>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSLayoutConstraint() { }
	
};


__interface  INTERFACE_UUID("{C53278EE-B363-4650-A941-D688606954C1}") NSLayoutManagerClass  : public Iosapi::Quartzcore::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{5F2ED907-ACAD-4EC2-A224-BFA0EBD15C00}") NSLayoutManager  : public Iosapi::Foundation::NSObject 
{
	virtual void __cdecl setTextStorage(_di_NSTextStorage textStorage) = 0 ;
	virtual _di_NSTextStorage __cdecl textStorage() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl textContainers() = 0 ;
	virtual void __cdecl addTextContainer(_di_NSTextContainer container) = 0 ;
	virtual void __cdecl insertTextContainer(_di_NSTextContainer container, unsigned long atIndex) = 0 ;
	virtual void __cdecl removeTextContainerAtIndex(unsigned long index) = 0 ;
	virtual void __cdecl textContainerChangedGeometry(_di_NSTextContainer container) = 0 ;
	virtual void __cdecl setDelegate(void * delegate) = 0 ;
	virtual void * __cdecl delegate() = 0 ;
	virtual void __cdecl setShowsInvisibleCharacters(bool showsInvisibleCharacters) = 0 ;
	virtual bool __cdecl showsInvisibleCharacters() = 0 ;
	virtual void __cdecl setShowsControlCharacters(bool showsControlCharacters) = 0 ;
	virtual bool __cdecl showsControlCharacters() = 0 ;
	virtual void __cdecl setHyphenationFactor(double hyphenationFactor) = 0 ;
	virtual double __cdecl hyphenationFactor() = 0 ;
	virtual void __cdecl setUsesFontLeading(bool usesFontLeading) = 0 ;
	virtual bool __cdecl usesFontLeading() = 0 ;
	virtual void __cdecl setAllowsNonContiguousLayout(bool allowsNonContiguousLayout) = 0 ;
	virtual bool __cdecl allowsNonContiguousLayout() = 0 ;
	virtual bool __cdecl hasNonContiguousLayout() = 0 ;
	virtual void __cdecl invalidateGlyphsForCharacterRange(Iosapi::Foundation::NSRange charRange, long changeInLength, Iosapi::Foundation::PNSRange actualCharacterRange) = 0 ;
	virtual void __cdecl invalidateLayoutForCharacterRange(Iosapi::Foundation::NSRange charRange, Iosapi::Foundation::PNSRange actualCharacterRange) = 0 ;
	virtual void __cdecl invalidateDisplayForCharacterRange(Iosapi::Foundation::NSRange charRange) = 0 ;
	virtual void __cdecl invalidateDisplayForGlyphRange(Iosapi::Foundation::NSRange glyphRange) = 0 ;
	virtual void __cdecl processEditingForTextStorage(_di_NSTextStorage textStorage, unsigned long edited, Iosapi::Foundation::NSRange range, long changeInLength, Iosapi::Foundation::NSRange invalidatedRange) = 0 ;
	virtual void __cdecl ensureGlyphsForCharacterRange(Iosapi::Foundation::NSRange charRange) = 0 ;
	virtual void __cdecl ensureGlyphsForGlyphRange(Iosapi::Foundation::NSRange glyphRange) = 0 ;
	virtual void __cdecl ensureLayoutForCharacterRange(Iosapi::Foundation::NSRange charRange) = 0 ;
	virtual void __cdecl ensureLayoutForGlyphRange(Iosapi::Foundation::NSRange glyphRange) = 0 ;
	virtual void __cdecl ensureLayoutForTextContainer(_di_NSTextContainer container) = 0 ;
	virtual void __cdecl ensureLayoutForBoundingRect(Iosapi::Foundation::NSRect bounds, _di_NSTextContainer inTextContainer) = 0 ;
	virtual void __cdecl setGlyphs(System::Word glyphs, long properties, unsigned long characterIndexes, _di_UIFont font, Iosapi::Foundation::NSRange forGlyphRange) = 0 ;
	virtual unsigned long __cdecl numberOfGlyphs() = 0 ;
	virtual System::Word __cdecl glyphAtIndexIsValidIndex(unsigned long glyphIndex, bool isValidIndex) = 0 ;
	virtual System::Word __cdecl glyphAtIndex(unsigned long glyphIndex) = 0 ;
	virtual bool __cdecl isValidGlyphIndex(unsigned long glyphIndex) = 0 ;
	virtual long __cdecl propertyForGlyphAtIndex(unsigned long glyphIndex) = 0 ;
	virtual unsigned long __cdecl characterIndexForGlyphAtIndex(unsigned long glyphIndex) = 0 ;
	virtual unsigned long __cdecl glyphIndexForCharacterAtIndex(unsigned long charIndex) = 0 ;
	virtual unsigned long __cdecl getGlyphsInRange(Iosapi::Foundation::NSRange glyphRange, System::Word glyphs, long properties, unsigned long characterIndexes, System::Byte bidiLevels) = 0 ;
	virtual void __cdecl setTextContainer(_di_NSTextContainer container, Iosapi::Foundation::NSRange forGlyphRange) = 0 ;
	virtual void __cdecl setLineFragmentRect(Iosapi::Foundation::NSRect fragmentRect, Iosapi::Foundation::NSRange forGlyphRange, Iosapi::Foundation::NSRect usedRect) = 0 ;
	virtual void __cdecl setExtraLineFragmentRect(Iosapi::Foundation::NSRect fragmentRect, Iosapi::Foundation::NSRect usedRect, _di_NSTextContainer textContainer) = 0 ;
	virtual void __cdecl setLocation(Iosapi::Foundation::NSPoint location, Iosapi::Foundation::NSRange forStartOfGlyphRange) = 0 ;
	virtual void __cdecl setNotShownAttribute(bool flag, unsigned long forGlyphAtIndex) = 0 ;
	virtual void __cdecl setDrawsOutsideLineFragment(bool flag, unsigned long forGlyphAtIndex) = 0 ;
	virtual void __cdecl setAttachmentSize(Iosapi::Foundation::NSSize attachmentSize, Iosapi::Foundation::NSRange forGlyphRange) = 0 ;
	virtual void __cdecl getFirstUnlaidCharacterIndex(unsigned long charIndex, unsigned long glyphIndex) = 0 ;
	virtual unsigned long __cdecl firstUnlaidCharacterIndex() = 0 ;
	virtual unsigned long __cdecl firstUnlaidGlyphIndex() = 0 ;
	virtual _di_NSTextContainer __cdecl textContainerForGlyphAtIndex(unsigned long glyphIndex, Iosapi::Foundation::PNSRange effectiveRange) = 0 ;
	virtual Iosapi::Foundation::NSRect __cdecl usedRectForTextContainer(_di_NSTextContainer container) = 0 ;
	virtual Iosapi::Foundation::NSRect __cdecl lineFragmentRectForGlyphAtIndex(unsigned long glyphIndex, Iosapi::Foundation::PNSRange effectiveRange) = 0 ;
	virtual Iosapi::Foundation::NSRect __cdecl lineFragmentUsedRectForGlyphAtIndex(unsigned long glyphIndex, Iosapi::Foundation::PNSRange effectiveRange) = 0 ;
	virtual Iosapi::Foundation::NSRect __cdecl extraLineFragmentRect() = 0 ;
	virtual Iosapi::Foundation::NSRect __cdecl extraLineFragmentUsedRect() = 0 ;
	virtual _di_NSTextContainer __cdecl extraLineFragmentTextContainer() = 0 ;
	virtual Iosapi::Foundation::NSPoint __cdecl locationForGlyphAtIndex(unsigned long glyphIndex) = 0 ;
	virtual bool __cdecl notShownAttributeForGlyphAtIndex(unsigned long glyphIndex) = 0 ;
	virtual bool __cdecl drawsOutsideLineFragmentForGlyphAtIndex(unsigned long glyphIndex) = 0 ;
	virtual Iosapi::Foundation::NSSize __cdecl attachmentSizeForGlyphAtIndex(unsigned long glyphIndex) = 0 ;
	virtual Iosapi::Foundation::NSRange __cdecl truncatedGlyphRangeInLineFragmentForGlyphAtIndex(unsigned long glyphIndex) = 0 ;
	virtual Iosapi::Foundation::NSRange __cdecl glyphRangeForCharacterRange(Iosapi::Foundation::NSRange charRange, Iosapi::Foundation::PNSRange actualCharacterRange) = 0 ;
	virtual Iosapi::Foundation::NSRange __cdecl characterRangeForGlyphRange(Iosapi::Foundation::NSRange glyphRange, Iosapi::Foundation::PNSRange actualGlyphRange) = 0 ;
	virtual Iosapi::Foundation::NSRange __cdecl glyphRangeForTextContainer(_di_NSTextContainer container) = 0 ;
	virtual Iosapi::Foundation::NSRange __cdecl rangeOfNominallySpacedGlyphsContainingIndex(unsigned long glyphIndex) = 0 ;
	virtual Iosapi::Foundation::NSRect __cdecl boundingRectForGlyphRange(Iosapi::Foundation::NSRange glyphRange, _di_NSTextContainer inTextContainer) = 0 ;
	virtual Iosapi::Foundation::NSRange __cdecl glyphRangeForBoundingRect(Iosapi::Foundation::NSRect bounds, _di_NSTextContainer inTextContainer) = 0 ;
	virtual Iosapi::Foundation::NSRange __cdecl glyphRangeForBoundingRectWithoutAdditionalLayout(Iosapi::Foundation::NSRect bounds, _di_NSTextContainer inTextContainer) = 0 ;
	virtual unsigned long __cdecl glyphIndexForPointInTextContainerFractionOfDistanceThroughGlyph(Iosapi::Foundation::NSPoint point, _di_NSTextContainer inTextContainer, Iosapi::Cocoatypes::PCGFloat fractionOfDistanceThroughGlyph) = 0 ;
	virtual unsigned long __cdecl glyphIndexForPointInTextContainer(Iosapi::Foundation::NSPoint point, _di_NSTextContainer inTextContainer) = 0 ;
	virtual double __cdecl fractionOfDistanceThroughGlyphForPoint(Iosapi::Foundation::NSPoint point, _di_NSTextContainer inTextContainer) = 0 ;
	virtual unsigned long __cdecl characterIndexForPoint(Iosapi::Foundation::NSPoint point, _di_NSTextContainer inTextContainer, Iosapi::Cocoatypes::PCGFloat fractionOfDistanceBetweenInsertionPoints) = 0 ;
	virtual unsigned long __cdecl getLineFragmentInsertionPointsForCharacterAtIndex(unsigned long charIndex, bool alternatePositions, bool inDisplayOrder, Iosapi::Cocoatypes::PCGFloat positions, unsigned long characterIndexes) = 0 ;
	virtual void __cdecl enumerateLineFragmentsForGlyphRange(Iosapi::Foundation::NSRange glyphRange, TUIKitUsingBlock usingBlock) = 0 ;
	virtual void __cdecl enumerateEnclosingRectsForGlyphRange(Iosapi::Foundation::NSRange glyphRange, Iosapi::Foundation::NSRange withinSelectedGlyphRange, _di_NSTextContainer inTextContainer, TUIKitUsingBlock1 usingBlock) = 0 ;
	virtual void __cdecl drawBackgroundForGlyphRange(Iosapi::Foundation::NSRange glyphsToShow, Iosapi::Foundation::NSPoint atPoint) = 0 ;
	virtual void __cdecl drawGlyphsForGlyphRange(Iosapi::Foundation::NSRange glyphsToShow, Iosapi::Foundation::NSPoint atPoint) = 0 ;
	virtual void __cdecl showCGGlyphs(System::Word glyphs, void * positions, unsigned long count, _di_UIFont font, Iosapi::Coregraphics::CGAffineTransform matrix, Iosapi::Foundation::_di_NSDictionary attributes, void * inContext) = 0 ;
	virtual void __cdecl fillBackgroundRectArray(void * rectArray, unsigned long count, Iosapi::Foundation::NSRange forCharacterRange, _di_UIColor color) = 0 ;
	virtual void __cdecl drawUnderlineForGlyphRange(Iosapi::Foundation::NSRange glyphRange, long underlineType, double baselineOffset, Iosapi::Foundation::NSRect lineFragmentRect, Iosapi::Foundation::NSRange lineFragmentGlyphRange, Iosapi::Foundation::NSPoint containerOrigin) = 0 ;
	virtual void __cdecl underlineGlyphRange(Iosapi::Foundation::NSRange glyphRange, long underlineType, Iosapi::Foundation::NSRect lineFragmentRect, Iosapi::Foundation::NSRange lineFragmentGlyphRange, Iosapi::Foundation::NSPoint containerOrigin) = 0 ;
	virtual void __cdecl drawStrikethroughForGlyphRange(Iosapi::Foundation::NSRange glyphRange, long strikethroughType, double baselineOffset, Iosapi::Foundation::NSRect lineFragmentRect, Iosapi::Foundation::NSRange lineFragmentGlyphRange, Iosapi::Foundation::NSPoint containerOrigin) = 0 ;
	virtual void __cdecl strikethroughGlyphRange(Iosapi::Foundation::NSRange glyphRange, long strikethroughType, Iosapi::Foundation::NSRect lineFragmentRect, Iosapi::Foundation::NSRange lineFragmentGlyphRange, Iosapi::Foundation::NSPoint containerOrigin) = 0 ;
};

class PASCALIMPLEMENTATION TNSLayoutManager : public Macapi::Objectivec::TOCGenericImport__2<_di_NSLayoutManagerClass,_di_NSLayoutManager>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSLayoutManagerClass,_di_NSLayoutManager> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSLayoutManager(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSLayoutManagerClass,_di_NSLayoutManager>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSLayoutManager() { }
	
};


__interface  INTERFACE_UUID("{40E16D91-F8F4-4DE4-A9F4-119314FF11BB}") NSTextStorageClass  : public Iosapi::Foundation::NSMutableAttributedStringClass 
{
	
};

__interface  INTERFACE_UUID("{0D02BF68-4599-49C9-A8BE-5F09277A80F1}") NSTextStorage  : public Iosapi::Foundation::NSMutableAttributedString 
{
	virtual Iosapi::Foundation::_di_NSArray __cdecl layoutManagers() = 0 ;
	virtual void __cdecl addLayoutManager(_di_NSLayoutManager aLayoutManager) = 0 ;
	virtual void __cdecl removeLayoutManager(_di_NSLayoutManager aLayoutManager) = 0 ;
	virtual void __cdecl setEditedMask(unsigned long editedMask) = 0 ;
	virtual unsigned long __cdecl editedMask() = 0 ;
	virtual void __cdecl setEditedRange(Iosapi::Foundation::NSRange editedRange) = 0 ;
	virtual Iosapi::Foundation::NSRange __cdecl editedRange() = 0 ;
	virtual void __cdecl setChangeInLength(long changeInLength) = 0 ;
	virtual long __cdecl changeInLength() = 0 ;
	virtual void __cdecl setDelegate(void * delegate) = 0 ;
	virtual void * __cdecl delegate() = 0 ;
	virtual void __cdecl edited(unsigned long editedMask, Iosapi::Foundation::NSRange range, long changeInLength) = 0 ;
	virtual void __cdecl processEditing() = 0 ;
	virtual bool __cdecl fixesAttributesLazily() = 0 ;
	virtual void __cdecl invalidateAttributesInRange(Iosapi::Foundation::NSRange range) = 0 ;
	virtual void __cdecl ensureAttributesAreFixedInRange(Iosapi::Foundation::NSRange range) = 0 ;
};

class PASCALIMPLEMENTATION TNSTextStorage : public Macapi::Objectivec::TOCGenericImport__2<_di_NSTextStorageClass,_di_NSTextStorage>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSTextStorageClass,_di_NSTextStorage> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSTextStorage(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSTextStorageClass,_di_NSTextStorage>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSTextStorage() { }
	
};


__interface  INTERFACE_UUID("{CB4BF3A8-9509-47D8-8A44-C96903303564}") UIFontDescriptorClass  : public Iosapi::Quartzcore::NSObjectClass 
{
	virtual _di_UIFontDescriptor __cdecl fontDescriptorWithFontAttributes(Iosapi::Foundation::_di_NSDictionary attributes) = 0 ;
	virtual _di_UIFontDescriptor __cdecl fontDescriptorWithNameSize(Iosapi::Foundation::_di_NSString fontName, double size) = 0 ;
	virtual _di_UIFontDescriptor __cdecl fontDescriptorWithNameMatrix(Iosapi::Foundation::_di_NSString fontName, Iosapi::Coregraphics::CGAffineTransform matrix) = 0 ;
	virtual _di_UIFontDescriptor __cdecl preferredFontDescriptorWithTextStyle(Iosapi::Foundation::_di_NSString style) = 0 ;
};

__interface  INTERFACE_UUID("{4E4A3072-20EE-468F-B5DD-897E00D7A3AE}") UIFontDescriptor  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::_di_NSString __cdecl postscriptName() = 0 ;
	virtual double __cdecl pointSize() = 0 ;
	virtual Iosapi::Coregraphics::CGAffineTransform __cdecl matrix() = 0 ;
	virtual unsigned __cdecl symbolicTraits() = 0 ;
	virtual void * __cdecl objectForKey(Iosapi::Foundation::_di_NSString anAttribute) = 0 ;
	virtual Iosapi::Foundation::_di_NSDictionary __cdecl fontAttributes() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl matchingFontDescriptorsWithMandatoryKeys(Iosapi::Foundation::_di_NSSet mandatoryKeys) = 0 ;
	virtual void * __cdecl initWithFontAttributes(Iosapi::Foundation::_di_NSDictionary attributes) = 0 ;
	virtual _di_UIFontDescriptor __cdecl fontDescriptorByAddingAttributes(Iosapi::Foundation::_di_NSDictionary attributes) = 0 ;
	virtual _di_UIFontDescriptor __cdecl fontDescriptorWithSymbolicTraits(unsigned symbolicTraits) = 0 ;
	virtual _di_UIFontDescriptor __cdecl fontDescriptorWithSize(double newPointSize) = 0 ;
	virtual _di_UIFontDescriptor __cdecl fontDescriptorWithMatrix(Iosapi::Coregraphics::CGAffineTransform matrix) = 0 ;
	virtual _di_UIFontDescriptor __cdecl fontDescriptorWithFace(Iosapi::Foundation::_di_NSString newFace) = 0 ;
	virtual _di_UIFontDescriptor __cdecl fontDescriptorWithFamily(Iosapi::Foundation::_di_NSString newFamily) = 0 ;
};

class PASCALIMPLEMENTATION TUIFontDescriptor : public Macapi::Objectivec::TOCGenericImport__2<_di_UIFontDescriptorClass,_di_UIFontDescriptor>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UIFontDescriptorClass,_di_UIFontDescriptor> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUIFontDescriptor(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UIFontDescriptorClass,_di_UIFontDescriptor>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUIFontDescriptor() { }
	
};


__interface  INTERFACE_UUID("{AE7FFB6F-7A06-4CCA-82E1-F7226513C7EB}") NSTextContainerClass  : public Iosapi::Quartzcore::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{FA34E82A-0ED3-4915-AF0F-4558B6A07D38}") NSTextContainer  : public Iosapi::Foundation::NSObject 
{
	virtual void * __cdecl initWithSize(Iosapi::Foundation::NSSize size) = 0 ;
	virtual void __cdecl setLayoutManager(_di_NSLayoutManager layoutManager) = 0 ;
	virtual _di_NSLayoutManager __cdecl layoutManager() = 0 ;
	virtual void __cdecl setSize(Iosapi::Foundation::NSSize size) = 0 ;
	virtual Iosapi::Foundation::NSSize __cdecl size() = 0 ;
	virtual void __cdecl setExclusionPaths(Iosapi::Foundation::_di_NSArray exclusionPaths) = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl exclusionPaths() = 0 ;
	virtual void __cdecl setLineBreakMode(long lineBreakMode) = 0 ;
	virtual long __cdecl lineBreakMode() = 0 ;
	virtual void __cdecl setLineFragmentPadding(double lineFragmentPadding) = 0 ;
	virtual double __cdecl lineFragmentPadding() = 0 ;
	virtual void __cdecl setMaximumNumberOfLines(unsigned long maximumNumberOfLines) = 0 ;
	virtual unsigned long __cdecl maximumNumberOfLines() = 0 ;
	virtual Iosapi::Foundation::NSRect __cdecl lineFragmentRectForProposedRect(Iosapi::Foundation::NSRect proposedRect, unsigned long atIndex, long writingDirection, void * remainingRect) = 0 ;
	virtual void __cdecl setWidthTracksTextView(bool widthTracksTextView) = 0 ;
	virtual bool __cdecl widthTracksTextView() = 0 ;
	virtual void __cdecl setHeightTracksTextView(bool heightTracksTextView) = 0 ;
	virtual bool __cdecl heightTracksTextView() = 0 ;
};

class PASCALIMPLEMENTATION TNSTextContainer : public Macapi::Objectivec::TOCGenericImport__2<_di_NSTextContainerClass,_di_NSTextContainer>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSTextContainerClass,_di_NSTextContainer> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSTextContainer(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSTextContainerClass,_di_NSTextContainer>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSTextContainer() { }
	
};


__interface  INTERFACE_UUID("{31C9E00A-F635-4B50-B011-B0210DEECE16}") NSTextTabClass  : public Iosapi::Quartzcore::NSObjectClass 
{
	virtual Iosapi::Foundation::_di_NSCharacterSet __cdecl columnTerminatorsForLocale(Iosapi::Foundation::_di_NSLocale aLocale) = 0 ;
};

__interface  INTERFACE_UUID("{AA8D0423-FC3E-4CC2-973A-AD088AC3DBEA}") NSTextTab  : public Iosapi::Foundation::NSObject 
{
	virtual void * __cdecl initWithTextAlignment(long alignment, double location, Iosapi::Foundation::_di_NSDictionary options) = 0 ;
	virtual long __cdecl alignment() = 0 ;
	virtual double __cdecl location() = 0 ;
	virtual Iosapi::Foundation::_di_NSDictionary __cdecl options() = 0 ;
};

class PASCALIMPLEMENTATION TNSTextTab : public Macapi::Objectivec::TOCGenericImport__2<_di_NSTextTabClass,_di_NSTextTab>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSTextTabClass,_di_NSTextTab> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSTextTab(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSTextTabClass,_di_NSTextTab>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSTextTab() { }
	
};


__interface  INTERFACE_UUID("{BAA1290B-2F73-4F5F-9719-7CB318B968A4}") NSParagraphStyleClass  : public Iosapi::Quartzcore::NSObjectClass 
{
	virtual _di_NSParagraphStyle __cdecl defaultParagraphStyle() = 0 ;
	virtual long __cdecl defaultWritingDirectionForLanguage(Iosapi::Foundation::_di_NSString languageName) = 0 ;
};

__interface  INTERFACE_UUID("{58BB0261-CED3-4DB7-8C59-0939DAC99A5C}") NSParagraphStyle  : public Iosapi::Foundation::NSObject 
{
	virtual double __cdecl lineSpacing() = 0 ;
	virtual double __cdecl paragraphSpacing() = 0 ;
	virtual long __cdecl alignment() = 0 ;
	virtual double __cdecl headIndent() = 0 ;
	virtual double __cdecl tailIndent() = 0 ;
	virtual double __cdecl firstLineHeadIndent() = 0 ;
	virtual double __cdecl minimumLineHeight() = 0 ;
	virtual double __cdecl maximumLineHeight() = 0 ;
	virtual long __cdecl lineBreakMode() = 0 ;
	virtual long __cdecl baseWritingDirection() = 0 ;
	virtual double __cdecl lineHeightMultiple() = 0 ;
	virtual double __cdecl paragraphSpacingBefore() = 0 ;
	virtual double __cdecl hyphenationFactor() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl tabStops() = 0 ;
	virtual double __cdecl defaultTabInterval() = 0 ;
};

class PASCALIMPLEMENTATION TNSParagraphStyle : public Macapi::Objectivec::TOCGenericImport__2<_di_NSParagraphStyleClass,_di_NSParagraphStyle>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSParagraphStyleClass,_di_NSParagraphStyle> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSParagraphStyle(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSParagraphStyleClass,_di_NSParagraphStyle>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSParagraphStyle() { }
	
};


__interface  INTERFACE_UUID("{36CA88FB-1718-498B-9447-512393F9D615}") NSMutableParagraphStyleClass  : public NSParagraphStyleClass 
{
	
};

__interface  INTERFACE_UUID("{364C9ADC-1858-457C-A987-DF8454B463A2}") NSMutableParagraphStyle  : public NSParagraphStyle 
{
	virtual void __cdecl setLineSpacing(double lineSpacing) = 0 ;
	HIDESBASE virtual double __cdecl lineSpacing() = 0 ;
	virtual void __cdecl setParagraphSpacing(double paragraphSpacing) = 0 ;
	HIDESBASE virtual double __cdecl paragraphSpacing() = 0 ;
	virtual void __cdecl setAlignment(long alignment) = 0 ;
	HIDESBASE virtual long __cdecl alignment() = 0 ;
	virtual void __cdecl setFirstLineHeadIndent(double firstLineHeadIndent) = 0 ;
	HIDESBASE virtual double __cdecl firstLineHeadIndent() = 0 ;
	virtual void __cdecl setHeadIndent(double headIndent) = 0 ;
	HIDESBASE virtual double __cdecl headIndent() = 0 ;
	virtual void __cdecl setTailIndent(double tailIndent) = 0 ;
	HIDESBASE virtual double __cdecl tailIndent() = 0 ;
	virtual void __cdecl setLineBreakMode(long lineBreakMode) = 0 ;
	HIDESBASE virtual long __cdecl lineBreakMode() = 0 ;
	virtual void __cdecl setMinimumLineHeight(double minimumLineHeight) = 0 ;
	HIDESBASE virtual double __cdecl minimumLineHeight() = 0 ;
	virtual void __cdecl setMaximumLineHeight(double maximumLineHeight) = 0 ;
	HIDESBASE virtual double __cdecl maximumLineHeight() = 0 ;
	virtual void __cdecl setBaseWritingDirection(long baseWritingDirection) = 0 ;
	HIDESBASE virtual long __cdecl baseWritingDirection() = 0 ;
	virtual void __cdecl setLineHeightMultiple(double lineHeightMultiple) = 0 ;
	HIDESBASE virtual double __cdecl lineHeightMultiple() = 0 ;
	virtual void __cdecl setParagraphSpacingBefore(double paragraphSpacingBefore) = 0 ;
	HIDESBASE virtual double __cdecl paragraphSpacingBefore() = 0 ;
	virtual void __cdecl setHyphenationFactor(double hyphenationFactor) = 0 ;
	HIDESBASE virtual double __cdecl hyphenationFactor() = 0 ;
	virtual void __cdecl setTabStops(Iosapi::Foundation::_di_NSArray tabStops) = 0 ;
	HIDESBASE virtual Iosapi::Foundation::_di_NSArray __cdecl tabStops() = 0 ;
	virtual void __cdecl setDefaultTabInterval(double defaultTabInterval) = 0 ;
	HIDESBASE virtual double __cdecl defaultTabInterval() = 0 ;
};

class PASCALIMPLEMENTATION TNSMutableParagraphStyle : public Macapi::Objectivec::TOCGenericImport__2<_di_NSMutableParagraphStyleClass,_di_NSMutableParagraphStyle>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSMutableParagraphStyleClass,_di_NSMutableParagraphStyle> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSMutableParagraphStyle(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSMutableParagraphStyleClass,_di_NSMutableParagraphStyle>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSMutableParagraphStyle() { }
	
};


__interface  INTERFACE_UUID("{E99993D6-47DD-42BC-826E-613FA92D4DCA}") NSShadowClass  : public Iosapi::Quartzcore::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{DD75575F-4191-4D8F-BDB3-96A9BA393A79}") NSShadow  : public Iosapi::Foundation::NSObject 
{
	virtual void __cdecl setShadowOffset(Iosapi::Foundation::NSSize shadowOffset) = 0 ;
	virtual Iosapi::Foundation::NSSize __cdecl shadowOffset() = 0 ;
	virtual void __cdecl setShadowBlurRadius(double shadowBlurRadius) = 0 ;
	virtual double __cdecl shadowBlurRadius() = 0 ;
	virtual void __cdecl setShadowColor(void * shadowColor) = 0 ;
	virtual void * __cdecl shadowColor() = 0 ;
};

class PASCALIMPLEMENTATION TNSShadow : public Macapi::Objectivec::TOCGenericImport__2<_di_NSShadowClass,_di_NSShadow>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSShadowClass,_di_NSShadow> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSShadow(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSShadowClass,_di_NSShadow>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSShadow() { }
	
};


__interface  INTERFACE_UUID("{9D2B0D14-063A-437D-A56D-7E7397C6FA21}") NSStringDrawingContextClass  : public Iosapi::Quartzcore::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{982AE15C-D76B-407B-89E2-A48DB0C465BB}") NSStringDrawingContext  : public Iosapi::Foundation::NSObject 
{
	virtual void __cdecl setMinimumScaleFactor(double minimumScaleFactor) = 0 ;
	virtual double __cdecl minimumScaleFactor() = 0 ;
	virtual void __cdecl setMinimumTrackingAdjustment(double minimumTrackingAdjustment) = 0 ;
	virtual double __cdecl minimumTrackingAdjustment() = 0 ;
	virtual double __cdecl actualScaleFactor() = 0 ;
	virtual double __cdecl actualTrackingAdjustment() = 0 ;
	virtual Iosapi::Foundation::NSRect __cdecl totalBounds() = 0 ;
};

class PASCALIMPLEMENTATION TNSStringDrawingContext : public Macapi::Objectivec::TOCGenericImport__2<_di_NSStringDrawingContextClass,_di_NSStringDrawingContext>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSStringDrawingContextClass,_di_NSStringDrawingContext> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSStringDrawingContext(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSStringDrawingContextClass,_di_NSStringDrawingContext>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSStringDrawingContext() { }
	
};


__interface  INTERFACE_UUID("{3B7DC8E2-6BEB-4A5B-846B-F33D38FD40AF}") NSTextAttachmentClass  : public Iosapi::Quartzcore::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{45A6BFBF-48C9-4611-B920-EABB4B72FF0B}") NSTextAttachment  : public Iosapi::Foundation::NSObject 
{
	virtual void * __cdecl initWithData(Iosapi::Foundation::_di_NSData contentData, Iosapi::Foundation::_di_NSString uti) = 0 ;
	virtual void __cdecl setContents(Iosapi::Foundation::_di_NSData contents) = 0 ;
	virtual Iosapi::Foundation::_di_NSData __cdecl contents() = 0 ;
	virtual void __cdecl setFileType(Iosapi::Foundation::_di_NSString fileType) = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl fileType() = 0 ;
	virtual void __cdecl setFileWrapper(Iosapi::Foundation::_di_NSFileWrapper fileWrapper) = 0 ;
	virtual Iosapi::Foundation::_di_NSFileWrapper __cdecl fileWrapper() = 0 ;
	virtual void __cdecl setImage(_di_UIImage image) = 0 ;
	virtual _di_UIImage __cdecl image() = 0 ;
	virtual void __cdecl setBounds(Iosapi::Foundation::NSRect bounds) = 0 ;
	virtual Iosapi::Foundation::NSRect __cdecl bounds() = 0 ;
};

class PASCALIMPLEMENTATION TNSTextAttachment : public Macapi::Objectivec::TOCGenericImport__2<_di_NSTextAttachmentClass,_di_NSTextAttachment>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSTextAttachmentClass,_di_NSTextAttachment> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSTextAttachment(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSTextAttachmentClass,_di_NSTextAttachment>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSTextAttachment() { }
	
};


__interface  INTERFACE_UUID("{A63E10C2-E248-46F7-AE2B-8E57C274A99F}") UIKeyCommandClass  : public Iosapi::Quartzcore::NSObjectClass 
{
	virtual _di_UIKeyCommand __cdecl keyCommandWithInput(Iosapi::Foundation::_di_NSString input, long modifierFlags, void * action) = 0 ;
};

__interface  INTERFACE_UUID("{031CC277-0AFA-44AA-AF33-27653BF7ABAD}") UIKeyCommand  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::_di_NSString __cdecl input() = 0 ;
	virtual long __cdecl modifierFlags() = 0 ;
};

class PASCALIMPLEMENTATION TUIKeyCommand : public Macapi::Objectivec::TOCGenericImport__2<_di_UIKeyCommandClass,_di_UIKeyCommand>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UIKeyCommandClass,_di_UIKeyCommand> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUIKeyCommand(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UIKeyCommandClass,_di_UIKeyCommand>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUIKeyCommand() { }
	
};


__interface  INTERFACE_UUID("{231F5CCE-09F7-44E8-8B17-EB987D428BA9}") UITextInputModeClass  : public Iosapi::Quartzcore::NSObjectClass 
{
	virtual Iosapi::Foundation::_di_NSArray __cdecl activeInputModes() = 0 ;
	virtual void * __cdecl currentInputMode() = 0 ;
};

__interface  INTERFACE_UUID("{223FED6C-FFF2-46FE-B401-A87AD479EE49}") UITextInputMode  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::_di_NSString __cdecl primaryLanguage() = 0 ;
};

class PASCALIMPLEMENTATION TUITextInputMode : public Macapi::Objectivec::TOCGenericImport__2<_di_UITextInputModeClass,_di_UITextInputMode>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UITextInputModeClass,_di_UITextInputMode> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUITextInputMode(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UITextInputModeClass,_di_UITextInputMode>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUITextInputMode() { }
	
};


__interface  INTERFACE_UUID("{E30BC5C6-6047-4586-A88A-A01C7F198CFF}") UIKitAdditions  : public Macapi::Objectivec::IObjectiveC 
{
	virtual void * __cdecl initWithColor(_di_UIColor color) = 0 ;
};

__interface  INTERFACE_UUID("{9E66DBC3-A676-4B4A-955A-326AFBD4F300}") UITraitCollectionClass  : public Iosapi::Quartzcore::NSObjectClass 
{
	virtual _di_UITraitCollection __cdecl currentTraitCollection() = 0 ;
	virtual void __cdecl setCurrentTraitCollection(_di_UITraitCollection currentTraitCollection) = 0 ;
	virtual _di_UITraitCollection __cdecl traitCollectionWithDisplayScale(double scale) = 0 ;
	virtual _di_UITraitCollection __cdecl traitCollectionWithHorizontalSizeClass(long horizontalSizeClass) = 0 ;
	virtual _di_UITraitCollection __cdecl traitCollectionWithTraitsFromCollections(Iosapi::Foundation::_di_NSArray traitCollections) = 0 ;
	virtual _di_UITraitCollection __cdecl traitCollectionWithUserInterfaceIdiom(long idiom) = 0 ;
	virtual _di_UITraitCollection __cdecl traitCollectionWithUserInterfaceStyle(long userInterfaceStyle) = 0 ;
	virtual _di_UITraitCollection __cdecl traitCollectionWithVerticalSizeClass(long verticalSizeClass) = 0 ;
};

__interface  INTERFACE_UUID("{8939A7C6-9790-44B1-B1B9-0169E400C997}") UITraitCollection  : public Iosapi::Foundation::NSObject 
{
	virtual bool __cdecl containsTraitsInCollection(_di_UITraitCollection trait) = 0 ;
	virtual double __cdecl displayScale() = 0 ;
	virtual bool __cdecl hasDifferentColorAppearanceComparedToTraitCollection(_di_UITraitCollection traitCollection) = 0 ;
	virtual long __cdecl horizontalSizeClass() = 0 ;
	virtual void * __cdecl initWithCoder(Iosapi::Foundation::_di_NSCoder coder) = 0 ;
	virtual long __cdecl userInterfaceIdiom() = 0 ;
	virtual long __cdecl userInterfaceStyle() = 0 ;
	virtual long __cdecl verticalSizeClass() = 0 ;
};

class PASCALIMPLEMENTATION TUITraitCollection : public Macapi::Objectivec::TOCGenericImport__2<_di_UITraitCollectionClass,_di_UITraitCollection>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UITraitCollectionClass,_di_UITraitCollection> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUITraitCollection(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UITraitCollectionClass,_di_UITraitCollection>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUITraitCollection() { }
	
};


typedef void * PUITraitCollection;

__interface  INTERFACE_UUID("{52E664EE-1A01-486A-9A9B-9647BCDCA370}") UITraitEnvironmentClass  : public Iosapi::Quartzcore::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{3E6DB638-EA4F-404E-8C1A-01542A327EF0}") UITraitEnvironment  : public Iosapi::Foundation::NSObject 
{
	virtual _di_UITraitCollection __cdecl traitCollection() = 0 ;
	virtual void __cdecl traitCollectionDidChange(_di_UITraitCollection previousTraitCollection) = 0 ;
};

class PASCALIMPLEMENTATION TUITraitEnvironment : public Macapi::Objectivec::TOCGenericImport__2<_di_UITraitEnvironmentClass,_di_UITraitEnvironment>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UITraitEnvironmentClass,_di_UITraitEnvironment> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUITraitEnvironment(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UITraitEnvironmentClass,_di_UITraitEnvironment>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUITraitEnvironment() { }
	
};


__interface  INTERFACE_UUID("{61F5DDE1-7D26-4CC6-BBAE-EFCBBEB5037D}") UIDynamicAnimatorClass  : public Iosapi::Quartzcore::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{B45E0388-8D78-47C5-AAAB-E97E92227292}") UIDynamicAnimator  : public Iosapi::Foundation::NSObject 
{
	virtual void * __cdecl initWithReferenceView(_di_UIView view) = 0 ;
	virtual void __cdecl addBehavior(_di_UIDynamicBehavior behavior) = 0 ;
	virtual void __cdecl removeBehavior(_di_UIDynamicBehavior behavior) = 0 ;
	virtual void __cdecl removeAllBehaviors() = 0 ;
	virtual _di_UIView __cdecl referenceView() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl behaviors() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl itemsInRect(Iosapi::Foundation::NSRect rect) = 0 ;
	virtual void __cdecl updateItemUsingCurrentState(void * item) = 0 ;
	virtual bool __cdecl isRunning() = 0 ;
	virtual double __cdecl elapsedTime() = 0 ;
	virtual void __cdecl setDelegate(void * delegate) = 0 ;
	virtual void * __cdecl delegate() = 0 ;
	virtual void * __cdecl initWithCollectionViewLayout(_di_UICollectionViewLayout layout) = 0 ;
	virtual _di_UICollectionViewLayoutAttributes __cdecl layoutAttributesForCellAtIndexPath(Iosapi::Foundation::_di_NSIndexPath indexPath) = 0 ;
	virtual _di_UICollectionViewLayoutAttributes __cdecl layoutAttributesForSupplementaryViewOfKind(Iosapi::Foundation::_di_NSString kind, Iosapi::Foundation::_di_NSIndexPath atIndexPath) = 0 ;
	virtual _di_UICollectionViewLayoutAttributes __cdecl layoutAttributesForDecorationViewOfKind(Iosapi::Foundation::_di_NSString decorationViewKind, Iosapi::Foundation::_di_NSIndexPath atIndexPath) = 0 ;
};

class PASCALIMPLEMENTATION TUIDynamicAnimator : public Macapi::Objectivec::TOCGenericImport__2<_di_UIDynamicAnimatorClass,_di_UIDynamicAnimator>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UIDynamicAnimatorClass,_di_UIDynamicAnimator> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUIDynamicAnimator(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UIDynamicAnimatorClass,_di_UIDynamicAnimator>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUIDynamicAnimator() { }
	
};


typedef void * PUIDynamicAnimator;

__interface  INTERFACE_UUID("{F0310543-2484-4C83-844F-6686A40254F9}") UIDynamicBehaviorClass  : public Iosapi::Quartzcore::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{8AF19804-1F5C-4C88-939E-AA8F28AB985D}") UIDynamicBehavior  : public Iosapi::Foundation::NSObject 
{
	virtual void __cdecl addChildBehavior(_di_UIDynamicBehavior behavior) = 0 ;
	virtual void __cdecl removeChildBehavior(_di_UIDynamicBehavior behavior) = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl childBehaviors() = 0 ;
	virtual void __cdecl setAction(TUIKitAction action) = 0 ;
	virtual TUIKitAction __cdecl action() = 0 ;
	virtual void __cdecl willMoveToAnimator(_di_UIDynamicAnimator dynamicAnimator) = 0 ;
	virtual _di_UIDynamicAnimator __cdecl dynamicAnimator() = 0 ;
};

class PASCALIMPLEMENTATION TUIDynamicBehavior : public Macapi::Objectivec::TOCGenericImport__2<_di_UIDynamicBehaviorClass,_di_UIDynamicBehavior>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UIDynamicBehaviorClass,_di_UIDynamicBehavior> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUIDynamicBehavior(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UIDynamicBehaviorClass,_di_UIDynamicBehavior>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUIDynamicBehavior() { }
	
};


typedef void * PUIDynamicBehavior;

__interface  INTERFACE_UUID("{6456BA57-C3C4-45EF-BF6B-A970C8CCD7C0}") UIMenuItemClass  : public Iosapi::Quartzcore::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{8A757229-EB63-4B02-9B98-97D88C9E25E9}") UIMenuItem  : public Iosapi::Foundation::NSObject 
{
	virtual void * __cdecl action() = 0 ;
	virtual void * __cdecl initWithTitle(Iosapi::Foundation::_di_NSString title, void * action) = 0 ;
	virtual void __cdecl setAction(void * action) = 0 ;
	virtual void __cdecl setTitle(Iosapi::Foundation::_di_NSString title) = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl title() = 0 ;
};

class PASCALIMPLEMENTATION TUIMenuItem : public Macapi::Objectivec::TOCGenericImport__2<_di_UIMenuItemClass,_di_UIMenuItem>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UIMenuItemClass,_di_UIMenuItem> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUIMenuItem(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UIMenuItemClass,_di_UIMenuItem>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUIMenuItem() { }
	
};


__interface  INTERFACE_UUID("{52CB7F2E-CB26-4121-979D-5020E934B090}") UIMenuControllerClass  : public Iosapi::Quartzcore::NSObjectClass 
{
	virtual void * __cdecl sharedMenuController() = 0 ;
};

__interface  INTERFACE_UUID("{AC1666FB-0C58-483E-94AD-99F949FABAA8}") UIMenuController  : public Iosapi::Foundation::NSObject 
{
	virtual long __cdecl arrowDirection() = 0 ;
	virtual bool __cdecl isMenuVisible() = 0 ;
	virtual Iosapi::Foundation::NSRect __cdecl menuFrame() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl menuItems() = 0 ;
	virtual void __cdecl setArrowDirection(long arrowDirection) = 0 ;
	virtual void __cdecl setMenuItems(Iosapi::Foundation::_di_NSArray menuItems) = 0 ;
	virtual void __cdecl setMenuVisible(bool menuVisible) = 0 /* overload */;
	virtual void __cdecl setMenuVisible(bool menuVisible, bool animated) = 0 /* overload */;
	virtual void __cdecl setTargetRect(Iosapi::Foundation::NSRect targetRect, _di_UIView inView) = 0 ;
	virtual void __cdecl update() = 0 ;
};

class PASCALIMPLEMENTATION TUIMenuController : public Macapi::Objectivec::TOCGenericImport__2<_di_UIMenuControllerClass,_di_UIMenuController>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UIMenuControllerClass,_di_UIMenuController> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUIMenuController(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UIMenuControllerClass,_di_UIMenuController>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUIMenuController() { }
	
};


__interface  INTERFACE_UUID("{4073F6E2-6B97-4FE1-9573-89C8869CD29D}") UINibClass  : public Iosapi::Quartzcore::NSObjectClass 
{
	virtual void * __cdecl nibWithData(Iosapi::Foundation::_di_NSData data, Iosapi::Foundation::_di_NSBundle bundle) = 0 ;
	virtual void * __cdecl nibWithNibName(Iosapi::Foundation::_di_NSString name, Iosapi::Foundation::_di_NSBundle bundle) = 0 ;
};

__interface  INTERFACE_UUID("{985317B5-E3E7-4FCD-A93A-B30242802B57}") UINib  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::_di_NSArray __cdecl instantiateWithOwner(void * ownerOrNil, Iosapi::Foundation::_di_NSDictionary options) = 0 ;
};

class PASCALIMPLEMENTATION TUINib : public Macapi::Objectivec::TOCGenericImport__2<_di_UINibClass,_di_UINib>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UINibClass,_di_UINib> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUINib(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UINibClass,_di_UINib>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUINib() { }
	
};


__interface  INTERFACE_UUID("{D15EAEB1-8D7B-42A0-94BF-CAC9B71B1D4F}") UINavigationItemClass  : public Iosapi::Quartzcore::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{8F5F3832-12EC-4BD4-A271-E4CD6B2A8C7B}") UINavigationItem  : public Iosapi::Foundation::NSObject 
{
	virtual _di_UIBarButtonItem __cdecl backBarButtonItem() = 0 ;
	virtual bool __cdecl hidesBackButton() = 0 ;
	virtual void * __cdecl initWithTitle(Iosapi::Foundation::_di_NSString title) = 0 ;
	virtual _di_UIBarButtonItem __cdecl leftBarButtonItem() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl leftBarButtonItems() = 0 ;
	virtual bool __cdecl leftItemsSupplementBackButton() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl prompt() = 0 ;
	virtual _di_UIBarButtonItem __cdecl rightBarButtonItem() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl rightBarButtonItems() = 0 ;
	virtual void __cdecl setBackBarButtonItem(_di_UIBarButtonItem backBarButtonItem) = 0 ;
	virtual void __cdecl setHidesBackButton(bool hidesBackButton) = 0 /* overload */;
	virtual void __cdecl setHidesBackButton(bool hidesBackButton, bool animated) = 0 /* overload */;
	virtual void __cdecl setLeftBarButtonItem(_di_UIBarButtonItem leftBarButtonItem) = 0 /* overload */;
	virtual void __cdecl setLeftBarButtonItem(_di_UIBarButtonItem item, bool animated) = 0 /* overload */;
	virtual void __cdecl setLeftBarButtonItems(Iosapi::Foundation::_di_NSArray leftBarButtonItems) = 0 /* overload */;
	virtual void __cdecl setLeftBarButtonItems(Iosapi::Foundation::_di_NSArray items, bool animated) = 0 /* overload */;
	virtual void __cdecl setLeftItemsSupplementBackButton(bool leftItemsSupplementBackButton) = 0 ;
	virtual void __cdecl setPrompt(Iosapi::Foundation::_di_NSString prompt) = 0 ;
	virtual void __cdecl setRightBarButtonItem(_di_UIBarButtonItem rightBarButtonItem) = 0 /* overload */;
	virtual void __cdecl setRightBarButtonItem(_di_UIBarButtonItem item, bool animated) = 0 /* overload */;
	virtual void __cdecl setRightBarButtonItems(Iosapi::Foundation::_di_NSArray rightBarButtonItems) = 0 /* overload */;
	virtual void __cdecl setRightBarButtonItems(Iosapi::Foundation::_di_NSArray items, bool animated) = 0 /* overload */;
	virtual void __cdecl setTitle(Iosapi::Foundation::_di_NSString title) = 0 ;
	virtual void __cdecl setTitleView(_di_UIView titleView) = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl title() = 0 ;
	virtual _di_UIView __cdecl titleView() = 0 ;
};

class PASCALIMPLEMENTATION TUINavigationItem : public Macapi::Objectivec::TOCGenericImport__2<_di_UINavigationItemClass,_di_UINavigationItem>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UINavigationItemClass,_di_UINavigationItem> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUINavigationItem(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UINavigationItemClass,_di_UINavigationItem>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUINavigationItem() { }
	
};


__interface  INTERFACE_UUID("{23C837B5-AFD9-4F1D-AD84-B5FA47F543D7}") UITextCheckerClass  : public Iosapi::Quartzcore::NSObjectClass 
{
	virtual Iosapi::Foundation::_di_NSArray __cdecl availableLanguages() = 0 ;
	virtual bool __cdecl hasLearnedWord(Iosapi::Foundation::_di_NSString word) = 0 ;
	virtual void __cdecl learnWord(Iosapi::Foundation::_di_NSString word) = 0 ;
	virtual void __cdecl unlearnWord(Iosapi::Foundation::_di_NSString word) = 0 ;
};

__interface  INTERFACE_UUID("{044966BA-33AD-48D8-BB77-6B1416C0F262}") UITextChecker  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::_di_NSArray __cdecl completionsForPartialWordRange(Iosapi::Foundation::NSRange range, Iosapi::Foundation::_di_NSString inString, Iosapi::Foundation::_di_NSString language) = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl guessesForWordRange(Iosapi::Foundation::NSRange range, Iosapi::Foundation::_di_NSString inString, Iosapi::Foundation::_di_NSString language) = 0 ;
	virtual void __cdecl ignoreWord(Iosapi::Foundation::_di_NSString wordToIgnore) = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl ignoredWords() = 0 ;
	virtual Iosapi::Foundation::NSRange __cdecl rangeOfMisspelledWordInString(Iosapi::Foundation::_di_NSString stringToCheck, Iosapi::Foundation::NSRange range, long startingAt, bool wrap, Iosapi::Foundation::_di_NSString language) = 0 ;
	virtual void __cdecl setIgnoredWords(Iosapi::Foundation::_di_NSArray words) = 0 ;
};

class PASCALIMPLEMENTATION TUITextChecker : public Macapi::Objectivec::TOCGenericImport__2<_di_UITextCheckerClass,_di_UITextChecker>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UITextCheckerClass,_di_UITextChecker> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUITextChecker(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UITextCheckerClass,_di_UITextChecker>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUITextChecker() { }
	
};


__interface  INTERFACE_UUID("{CB8A0C1F-B8D9-4C16-A24C-6B12A2CA66C2}") UILocalizedIndexedCollationClass  : public Iosapi::Quartzcore::NSObjectClass 
{
	virtual void * __cdecl currentCollation() = 0 ;
};

__interface  INTERFACE_UUID("{DAFD770B-86B8-4B35-8E08-C1BA4CB16584}") UILocalizedIndexedCollation  : public Iosapi::Foundation::NSObject 
{
	virtual long __cdecl sectionForObject(void * object_, void * collationStringSelector) = 0 ;
	virtual long __cdecl sectionForSectionIndexTitleAtIndex(long indexTitleIndex) = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl sectionIndexTitles() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl sectionTitles() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl sortedArrayFromArray(Iosapi::Foundation::_di_NSArray array_, void * collationStringSelector) = 0 ;
};

class PASCALIMPLEMENTATION TUILocalizedIndexedCollation : public Macapi::Objectivec::TOCGenericImport__2<_di_UILocalizedIndexedCollationClass,_di_UILocalizedIndexedCollation>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UILocalizedIndexedCollationClass,_di_UILocalizedIndexedCollation> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUILocalizedIndexedCollation(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UILocalizedIndexedCollationClass,_di_UILocalizedIndexedCollation>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUILocalizedIndexedCollation() { }
	
};


__interface  INTERFACE_UUID("{87E75615-9F27-4276-B747-7D5C8F3BAB5A}") UIImageClass  : public Iosapi::Quartzcore::NSObjectClass 
{
	virtual void * __cdecl animatedImageNamed(Iosapi::Foundation::_di_NSString name, double duration) = 0 ;
	virtual void * __cdecl animatedImageWithImages(Iosapi::Foundation::_di_NSArray images, double duration) = 0 ;
	virtual void * __cdecl animatedResizableImageNamed(Iosapi::Foundation::_di_NSString name, UIEdgeInsets capInsets, double duration) = 0 ;
	virtual void * __cdecl imageNamed(Iosapi::Foundation::_di_NSString name) = 0 ;
	virtual void * __cdecl imageWithCGImage(void * cgImage) = 0 /* overload */;
	virtual void * __cdecl imageWithCGImage(void * cgImage, double scale, long orientation) = 0 /* overload */;
	virtual void * __cdecl imageWithCIImage(Iosapi::Coreimage::_di_CIImage ciImage) = 0 ;
	virtual void * __cdecl imageWithContentsOfFile(Iosapi::Foundation::_di_NSString path) = 0 ;
	virtual void * __cdecl imageWithData(Iosapi::Foundation::_di_NSData data) = 0 ;
};

__interface  INTERFACE_UUID("{65BCAAA8-4DB4-4884-B05E-B09DC6D271A9}") UIImage  : public Iosapi::Foundation::NSObject 
{
	virtual void * __cdecl CGImage() = 0 ;
	virtual Iosapi::Coreimage::_di_CIImage __cdecl CIImage() = 0 ;
	virtual UIEdgeInsets __cdecl capInsets() = 0 ;
	virtual void __cdecl drawAsPatternInRect(Iosapi::Foundation::NSRect rect) = 0 ;
	virtual void __cdecl drawAtPoint(Iosapi::Foundation::NSPoint point) = 0 /* overload */;
	virtual void __cdecl drawAtPoint(Iosapi::Foundation::NSPoint point, unsigned blendMode, double alpha) = 0 /* overload */;
	virtual void __cdecl drawInRect(Iosapi::Foundation::NSRect rect) = 0 /* overload */;
	virtual void __cdecl drawInRect(Iosapi::Foundation::NSRect rect, unsigned blendMode, double alpha) = 0 /* overload */;
	virtual double __cdecl duration() = 0 ;
	virtual long __cdecl imageOrientation() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl images() = 0 ;
	virtual void * __cdecl initWithCGImage(void * cgImage) = 0 /* overload */;
	virtual void * __cdecl initWithCGImage(void * cgImage, double scale, long orientation) = 0 /* overload */;
	virtual void * __cdecl initWithCIImage(Iosapi::Coreimage::_di_CIImage ciImage) = 0 ;
	virtual void * __cdecl initWithContentsOfFile(Iosapi::Foundation::_di_NSString path) = 0 ;
	virtual void * __cdecl initWithData(Iosapi::Foundation::_di_NSData data) = 0 ;
	virtual long __cdecl leftCapWidth() = 0 ;
	virtual _di_UIImage __cdecl resizableImageWithCapInsets(UIEdgeInsets capInsets) = 0 ;
	virtual double __cdecl scale() = 0 ;
	virtual Iosapi::Foundation::NSSize __cdecl size() = 0 ;
	virtual _di_UIImage __cdecl stretchableImageWithLeftCapWidth(long leftCapWidth, long topCapHeight) = 0 ;
	virtual long __cdecl topCapHeight() = 0 ;
};

class PASCALIMPLEMENTATION TUIImage : public Macapi::Objectivec::TOCGenericImport__2<_di_UIImageClass,_di_UIImage>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UIImageClass,_di_UIImage> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUIImage(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UIImageClass,_di_UIImage>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUIImage() { }
	
};


__interface  INTERFACE_UUID("{EA6310B2-4446-44A2-9C1D-C37902A6FEC2}") UIGestureRecognizerClass  : public Iosapi::Quartzcore::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{3384D59C-6A05-4AEC-AAE2-8B5CABBAD157}") UIGestureRecognizer  : public Iosapi::Foundation::NSObject 
{
	virtual void __cdecl addTarget(void * target, void * action) = 0 ;
	virtual bool __cdecl canBePreventedByGestureRecognizer(_di_UIGestureRecognizer preventingGestureRecognizer) = 0 ;
	virtual bool __cdecl canPreventGestureRecognizer(_di_UIGestureRecognizer preventedGestureRecognizer) = 0 ;
	virtual bool __cdecl cancelsTouchesInView() = 0 ;
	virtual bool __cdecl delaysTouchesBegan() = 0 ;
	virtual bool __cdecl delaysTouchesEnded() = 0 ;
	virtual void * __cdecl delegate() = 0 ;
	virtual void __cdecl ignoreTouch(_di_UITouch touch, _di_UIEvent forEvent) = 0 ;
	virtual void * __cdecl initWithTarget(void * target, void * action) = 0 ;
	virtual bool __cdecl isEnabled() = 0 ;
	virtual Iosapi::Foundation::NSPoint __cdecl locationInView(_di_UIView view) = 0 ;
	virtual Iosapi::Foundation::NSPoint __cdecl locationOfTouch(unsigned long touchIndex, _di_UIView inView) = 0 ;
	virtual unsigned long __cdecl numberOfTouches() = 0 ;
	virtual void __cdecl removeTarget(void * target, void * action) = 0 ;
	virtual void __cdecl requireGestureRecognizerToFail(_di_UIGestureRecognizer otherGestureRecognizer) = 0 ;
	virtual void __cdecl reset() = 0 ;
	virtual void __cdecl setCancelsTouchesInView(bool cancelsTouchesInView) = 0 ;
	virtual void __cdecl setDelaysTouchesBegan(bool delaysTouchesBegan) = 0 ;
	virtual void __cdecl setDelaysTouchesEnded(bool delaysTouchesEnded) = 0 ;
	virtual void __cdecl setDelegate(void * delegate) = 0 ;
	virtual void __cdecl setEnabled(bool enabled) = 0 ;
	virtual void __cdecl setState(long state) = 0 ;
	virtual long __cdecl state() = 0 ;
	virtual void __cdecl touchesBegan(Iosapi::Foundation::_di_NSSet touches, _di_UIEvent withEvent) = 0 ;
	virtual void __cdecl touchesCancelled(Iosapi::Foundation::_di_NSSet touches, _di_UIEvent withEvent) = 0 ;
	virtual void __cdecl touchesEnded(Iosapi::Foundation::_di_NSSet touches, _di_UIEvent withEvent) = 0 ;
	virtual void __cdecl touchesMoved(Iosapi::Foundation::_di_NSSet touches, _di_UIEvent withEvent) = 0 ;
	virtual _di_UIView __cdecl view() = 0 ;
};

class PASCALIMPLEMENTATION TUIGestureRecognizer : public Macapi::Objectivec::TOCGenericImport__2<_di_UIGestureRecognizerClass,_di_UIGestureRecognizer>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UIGestureRecognizerClass,_di_UIGestureRecognizer> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUIGestureRecognizer(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UIGestureRecognizerClass,_di_UIGestureRecognizer>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUIGestureRecognizer() { }
	
};


__interface  INTERFACE_UUID("{EB22D6EF-BAAB-4448-8657-1FACB5BAD2B8}") UIFontClass  : public Iosapi::Quartzcore::NSObjectClass 
{
	virtual void * __cdecl boldSystemFontOfSize(double fontSize) = 0 ;
	virtual double __cdecl buttonFontSize() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl familyNames() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl fontNamesForFamilyName(Iosapi::Foundation::_di_NSString familyName) = 0 ;
	virtual void * __cdecl fontWithName(Iosapi::Foundation::_di_NSString fontName, double size) = 0 ;
	virtual void * __cdecl italicSystemFontOfSize(double fontSize) = 0 ;
	virtual double __cdecl labelFontSize() = 0 ;
	virtual double __cdecl smallSystemFontSize() = 0 ;
	virtual void * __cdecl systemFontOfSize(double fontSize) = 0 ;
	virtual double __cdecl systemFontSize() = 0 ;
};

__interface  INTERFACE_UUID("{B064BB36-A2A7-41B3-8BC8-A34E9401EDD6}") UIFont  : public Iosapi::Foundation::NSObject 
{
	virtual double __cdecl ascender() = 0 ;
	virtual double __cdecl capHeight() = 0 ;
	virtual double __cdecl descender() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl familyName() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl fontName() = 0 ;
	virtual _di_UIFont __cdecl fontWithSize(double fontSize) = 0 ;
	virtual double __cdecl leading() = 0 ;
	virtual double __cdecl lineHeight() = 0 ;
	virtual double __cdecl pointSize() = 0 ;
	virtual double __cdecl xHeight() = 0 ;
};

class PASCALIMPLEMENTATION TUIFont : public Macapi::Objectivec::TOCGenericImport__2<_di_UIFontClass,_di_UIFont>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UIFontClass,_di_UIFont> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUIFont(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UIFontClass,_di_UIFont>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUIFont() { }
	
};


__interface  INTERFACE_UUID("{BD63AA5F-BF1C-442A-B72A-526358F5E448}") UILocalNotificationClass  : public Iosapi::Quartzcore::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{5289169B-7A4F-46BE-8716-C10A780CBD0E}") UILocalNotification  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::_di_NSString __cdecl alertAction() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl alertBody() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl alertLaunchImage() = 0 ;
	virtual long __cdecl applicationIconBadgeNumber() = 0 ;
	virtual Iosapi::Foundation::_di_NSDate __cdecl fireDate() = 0 ;
	virtual bool __cdecl hasAction() = 0 ;
	virtual Iosapi::Foundation::_di_NSCalendar __cdecl repeatCalendar() = 0 ;
	virtual unsigned long __cdecl repeatInterval() = 0 ;
	virtual void __cdecl setAlertAction(Iosapi::Foundation::_di_NSString alertAction) = 0 ;
	virtual void __cdecl setAlertBody(Iosapi::Foundation::_di_NSString alertBody) = 0 ;
	virtual void __cdecl setAlertLaunchImage(Iosapi::Foundation::_di_NSString alertLaunchImage) = 0 ;
	virtual void __cdecl setApplicationIconBadgeNumber(long applicationIconBadgeNumber) = 0 ;
	virtual void __cdecl setFireDate(Iosapi::Foundation::_di_NSDate fireDate) = 0 ;
	virtual void __cdecl setHasAction(bool hasAction) = 0 ;
	virtual void __cdecl setRepeatCalendar(Iosapi::Foundation::_di_NSCalendar repeatCalendar) = 0 ;
	virtual void __cdecl setRepeatInterval(unsigned long repeatInterval) = 0 ;
	virtual void __cdecl setSoundName(Iosapi::Foundation::_di_NSString soundName) = 0 ;
	virtual void __cdecl setTimeZone(Iosapi::Foundation::_di_NSTimeZone timeZone) = 0 ;
	virtual void __cdecl setUserInfo(Iosapi::Foundation::_di_NSDictionary userInfo) = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl soundName() = 0 ;
	virtual Iosapi::Foundation::_di_NSTimeZone __cdecl timeZone() = 0 ;
	virtual Iosapi::Foundation::_di_NSDictionary __cdecl userInfo() = 0 ;
};

class PASCALIMPLEMENTATION TUILocalNotification : public Macapi::Objectivec::TOCGenericImport__2<_di_UILocalNotificationClass,_di_UILocalNotification>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UILocalNotificationClass,_di_UILocalNotification> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUILocalNotification(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UILocalNotificationClass,_di_UILocalNotification>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUILocalNotification() { }
	
};


__interface  INTERFACE_UUID("{B7142658-5285-4C9F-BC6C-74516DFEAD20}") UIUserNotificationSettingsClass  : public Iosapi::Quartzcore::NSObjectClass 
{
	virtual void * __cdecl settingsForTypes(unsigned long types, Iosapi::Foundation::_di_NSSet categories) = 0 ;
};

__interface  INTERFACE_UUID("{15F012FA-B58B-4A47-9E84-4D93D5BB6747}") UIUserNotificationSettings  : public Iosapi::Foundation::NSObject 
{
	virtual unsigned long __cdecl types() = 0 ;
	virtual Iosapi::Foundation::_di_NSSet __cdecl categories() = 0 ;
};

class PASCALIMPLEMENTATION TUIUserNotificationSettings : public Macapi::Objectivec::TOCGenericImport__2<_di_UIUserNotificationSettingsClass,_di_UIUserNotificationSettings>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UIUserNotificationSettingsClass,_di_UIUserNotificationSettings> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUIUserNotificationSettings(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UIUserNotificationSettingsClass,_di_UIUserNotificationSettings>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUIUserNotificationSettings() { }
	
};


__interface  INTERFACE_UUID("{8B90E087-EC9A-484C-9015-BE777FF3F861}") UITextInputStringTokenizerClass  : public Iosapi::Quartzcore::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{A5A33069-7715-4E1B-AD69-F71C9294CDD3}") UITextInputStringTokenizer  : public Iosapi::Foundation::NSObject 
{
	virtual void * __cdecl initWithTextInput(_di_UIResponder textInput) = 0 ;
};

class PASCALIMPLEMENTATION TUITextInputStringTokenizer : public Macapi::Objectivec::TOCGenericImport__2<_di_UITextInputStringTokenizerClass,_di_UITextInputStringTokenizer>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UITextInputStringTokenizerClass,_di_UITextInputStringTokenizer> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUITextInputStringTokenizer(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UITextInputStringTokenizerClass,_di_UITextInputStringTokenizer>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUITextInputStringTokenizer() { }
	
};


__interface  INTERFACE_UUID("{DABB3555-5B7F-4A3B-BF97-F43DAD3D5B42}") UITextRangeClass  : public Iosapi::Quartzcore::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{DD81F81D-99CB-4537-8245-13E633C1B8C0}") UITextRange  : public Iosapi::Foundation::NSObject 
{
	virtual bool __cdecl isEmpty() = 0 ;
	virtual _di_UITextPosition __cdecl start() = 0 ;
	virtual _di_UITextPosition __cdecl end() = 0 ;
};

class PASCALIMPLEMENTATION TUITextRange : public Macapi::Objectivec::TOCGenericImport__2<_di_UITextRangeClass,_di_UITextRange>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UITextRangeClass,_di_UITextRange> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUITextRange(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UITextRangeClass,_di_UITextRange>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUITextRange() { }
	
};


__interface  INTERFACE_UUID("{0CF607E1-7E08-4D61-AC23-656163E5D9B0}") UIScreenModeClass  : public Iosapi::Quartzcore::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{C9AB92D8-C120-40CB-B3B4-F2FA1DC9C9B0}") UIScreenMode  : public Iosapi::Foundation::NSObject 
{
	virtual double __cdecl pixelAspectRatio() = 0 ;
	virtual Iosapi::Foundation::NSSize __cdecl size() = 0 ;
};

class PASCALIMPLEMENTATION TUIScreenMode : public Macapi::Objectivec::TOCGenericImport__2<_di_UIScreenModeClass,_di_UIScreenMode>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UIScreenModeClass,_di_UIScreenMode> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUIScreenMode(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UIScreenModeClass,_di_UIScreenMode>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUIScreenMode() { }
	
};


__interface  INTERFACE_UUID("{E3A65960-2A9F-4A4A-BACE-E00E491F6AB0}") UIScreenClass  : public Iosapi::Quartzcore::NSObjectClass 
{
	virtual void * __cdecl mainScreen() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl screens() = 0 ;
};

__interface  INTERFACE_UUID("{9D84B3DC-E2BC-49A3-B311-C0E55FD780B9}") UIScreen  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::NSRect __cdecl applicationFrame() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl availableModes() = 0 ;
	virtual Iosapi::Foundation::NSRect __cdecl bounds() = 0 ;
	virtual double __cdecl brightness() = 0 ;
	virtual _di_UIScreenMode __cdecl currentMode() = 0 ;
	virtual Iosapi::Quartzcore::_di_CADisplayLink __cdecl displayLinkWithTarget(void * target, void * selector) = 0 ;
	virtual _di_UIScreen __cdecl mirroredScreen() = 0 ;
	virtual long __cdecl overscanCompensation() = 0 ;
	virtual _di_UIScreenMode __cdecl preferredMode() = 0 ;
	virtual double __cdecl scale() = 0 ;
	virtual void __cdecl setBrightness(double brightness) = 0 ;
	virtual void __cdecl setCurrentMode(_di_UIScreenMode currentMode) = 0 ;
	virtual void __cdecl setOverscanCompensation(long overscanCompensation) = 0 ;
	virtual void __cdecl setWantsSoftwareDimming(bool wantsSoftwareDimming) = 0 ;
	virtual bool __cdecl wantsSoftwareDimming() = 0 ;
	virtual void * __cdecl coordinateSpace() = 0 ;
	virtual void * __cdecl fixedCoordinateSpace() = 0 ;
	virtual Iosapi::Foundation::NSRect __cdecl nativeBounds() = 0 ;
	virtual double __cdecl nativeScale() = 0 ;
	virtual _di_UIView __cdecl snapshotViewAfterScreenUpdates(bool afterUpdates) = 0 ;
};

class PASCALIMPLEMENTATION TUIScreen : public Macapi::Objectivec::TOCGenericImport__2<_di_UIScreenClass,_di_UIScreen>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UIScreenClass,_di_UIScreen> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUIScreen(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UIScreenClass,_di_UIScreen>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUIScreen() { }
	
};


__interface  INTERFACE_UUID("{71125106-1FF5-44BD-BC31-72D31D04CF53}") UIResponderClass  : public Iosapi::Quartzcore::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{3294BC42-563A-4D5A-BE0D-391D08B4346D}") UIResponder  : public Iosapi::Foundation::NSObject 
{
	virtual bool __cdecl becomeFirstResponder() = 0 ;
	virtual bool __cdecl canBecomeFirstResponder() = 0 ;
	virtual bool __cdecl canPerformAction(void * action, void * withSender) = 0 ;
	virtual bool __cdecl canResignFirstResponder() = 0 ;
	virtual _di_UIView __cdecl inputAccessoryView() = 0 ;
	virtual _di_UIView __cdecl inputView() = 0 ;
	virtual bool __cdecl isFirstResponder() = 0 ;
	virtual void __cdecl motionBegan(long motion, _di_UIEvent withEvent) = 0 ;
	virtual void __cdecl motionCancelled(long motion, _di_UIEvent withEvent) = 0 ;
	virtual void __cdecl motionEnded(long motion, _di_UIEvent withEvent) = 0 ;
	virtual _di_UIResponder __cdecl nextResponder() = 0 ;
	virtual void __cdecl reloadInputViews() = 0 ;
	virtual void __cdecl remoteControlReceivedWithEvent(_di_UIEvent event) = 0 ;
	virtual bool __cdecl resignFirstResponder() = 0 ;
	virtual void __cdecl touchesBegan(Iosapi::Foundation::_di_NSSet touches, _di_UIEvent withEvent) = 0 ;
	virtual void __cdecl touchesCancelled(Iosapi::Foundation::_di_NSSet touches, _di_UIEvent withEvent) = 0 ;
	virtual void __cdecl touchesEnded(Iosapi::Foundation::_di_NSSet touches, _di_UIEvent withEvent) = 0 ;
	virtual void __cdecl touchesMoved(Iosapi::Foundation::_di_NSSet touches, _di_UIEvent withEvent) = 0 ;
	virtual Iosapi::Foundation::_di_NSUndoManager __cdecl undoManager() = 0 ;
};

class PASCALIMPLEMENTATION TUIResponder : public Macapi::Objectivec::TOCGenericImport__2<_di_UIResponderClass,_di_UIResponder>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UIResponderClass,_di_UIResponder> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUIResponder(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UIResponderClass,_di_UIResponder>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUIResponder() { }
	
};


__interface  INTERFACE_UUID("{D99EC40A-1C3D-48E3-9C1E-5421C2AB4D2C}") UIStoryboardClass  : public Iosapi::Quartzcore::NSObjectClass 
{
	virtual void * __cdecl storyboardWithName(Iosapi::Foundation::_di_NSString name, Iosapi::Foundation::_di_NSBundle bundle) = 0 ;
};

__interface  INTERFACE_UUID("{500AA1D9-5EDF-4AA4-90B8-66FB67F49B9D}") UIStoryboard  : public Iosapi::Foundation::NSObject 
{
	virtual void * __cdecl instantiateInitialViewController() = 0 ;
	virtual void * __cdecl instantiateViewControllerWithIdentifier(Iosapi::Foundation::_di_NSString identifier) = 0 ;
};

class PASCALIMPLEMENTATION TUIStoryboard : public Macapi::Objectivec::TOCGenericImport__2<_di_UIStoryboardClass,_di_UIStoryboard>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UIStoryboardClass,_di_UIStoryboard> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUIStoryboard(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UIStoryboardClass,_di_UIStoryboard>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUIStoryboard() { }
	
};


__interface  INTERFACE_UUID("{E80D1477-C651-41AD-B825-97125D6D3D43}") UISearchDisplayControllerClass  : public Iosapi::Quartzcore::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{C2D8D1A0-0EF0-4417-A5FC-1962B858410F}") UISearchDisplayController  : public Iosapi::Foundation::NSObject 
{
	virtual void * __cdecl delegate() = 0 ;
	virtual void * __cdecl initWithSearchBar(_di_UISearchBar searchBar, _di_UIViewController contentsController) = 0 ;
	virtual bool __cdecl isActive() = 0 ;
	virtual _di_UISearchBar __cdecl searchBar() = 0 ;
	virtual _di_UIViewController __cdecl searchContentsController() = 0 ;
	virtual void * __cdecl searchResultsDataSource() = 0 ;
	virtual void * __cdecl searchResultsDelegate() = 0 ;
	virtual _di_UITableView __cdecl searchResultsTableView() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl searchResultsTitle() = 0 ;
	virtual void __cdecl setActive(bool active) = 0 /* overload */;
	virtual void __cdecl setActive(bool visible, bool animated) = 0 /* overload */;
	virtual void __cdecl setDelegate(void * delegate) = 0 ;
	virtual void __cdecl setSearchResultsDataSource(void * searchResultsDataSource) = 0 ;
	virtual void __cdecl setSearchResultsDelegate(void * searchResultsDelegate) = 0 ;
	virtual void __cdecl setSearchResultsTitle(Iosapi::Foundation::_di_NSString searchResultsTitle) = 0 ;
};

class PASCALIMPLEMENTATION TUISearchDisplayController : public Macapi::Objectivec::TOCGenericImport__2<_di_UISearchDisplayControllerClass,_di_UISearchDisplayController>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UISearchDisplayControllerClass,_di_UISearchDisplayController> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUISearchDisplayController(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UISearchDisplayControllerClass,_di_UISearchDisplayController>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUISearchDisplayController() { }
	
};


__interface  INTERFACE_UUID("{E0D7DDAF-F418-4884-8A9E-09A43DE685CD}") UIStoryboardSegueClass  : public Iosapi::Quartzcore::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{38CD90EC-09B6-4A61-8FD5-59B08A111320}") UIStoryboardSegue  : public Iosapi::Foundation::NSObject 
{
	virtual void * __cdecl destinationViewController() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl identifier() = 0 ;
	virtual void * __cdecl initWithIdentifier(Iosapi::Foundation::_di_NSString identifier, _di_UIViewController source, _di_UIViewController destination) = 0 ;
	virtual void __cdecl perform() = 0 ;
	virtual void * __cdecl sourceViewController() = 0 ;
};

class PASCALIMPLEMENTATION TUIStoryboardSegue : public Macapi::Objectivec::TOCGenericImport__2<_di_UIStoryboardSegueClass,_di_UIStoryboardSegue>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UIStoryboardSegueClass,_di_UIStoryboardSegue> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUIStoryboardSegue(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UIStoryboardSegueClass,_di_UIStoryboardSegue>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUIStoryboardSegue() { }
	
};


__interface  INTERFACE_UUID("{2F65B178-F9A0-46E6-BCF3-07C925F709E2}") UIPresentationControllerClass  : public Iosapi::Quartzcore::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{06A466C5-BCC7-4EBE-B82C-B3A1FA7F0D22}") UIPresentationController  : public Iosapi::Foundation::NSObject 
{
	virtual _di_UIViewController __cdecl presentingViewController() = 0 ;
	virtual _di_UIViewController __cdecl presentedViewController() = 0 ;
	virtual long __cdecl presentationStyle() = 0 ;
	virtual _di_UIView __cdecl containerView() = 0 ;
	virtual void __cdecl setDelegate(void * delegate) = 0 ;
	virtual void * __cdecl delegate() = 0 ;
	virtual void * __cdecl initWithPresentedViewController(_di_UIViewController presentedViewController, _di_UIViewController presentingViewController) = 0 ;
	virtual long __cdecl adaptivePresentationStyle() = 0 ;
	virtual void __cdecl containerViewWillLayoutSubviews() = 0 ;
	virtual void __cdecl containerViewDidLayoutSubviews() = 0 ;
	virtual _di_UIView __cdecl presentedView() = 0 ;
	virtual Iosapi::Foundation::NSRect __cdecl frameOfPresentedViewInContainerView() = 0 ;
	virtual bool __cdecl shouldPresentInFullscreen() = 0 ;
	virtual bool __cdecl shouldRemovePresentersView() = 0 ;
	virtual void __cdecl presentationTransitionWillBegin() = 0 ;
	virtual void __cdecl presentationTransitionDidEnd(bool completed) = 0 ;
	virtual void __cdecl dismissalTransitionWillBegin() = 0 ;
	virtual void __cdecl dismissalTransitionDidEnd(bool completed) = 0 ;
	virtual void __cdecl setOverrideTraitCollection(_di_UITraitCollection overrideTraitCollection) = 0 ;
	virtual _di_UITraitCollection __cdecl overrideTraitCollection() = 0 ;
};

class PASCALIMPLEMENTATION TUIPresentationController : public Macapi::Objectivec::TOCGenericImport__2<_di_UIPresentationControllerClass,_di_UIPresentationController>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UIPresentationControllerClass,_di_UIPresentationController> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUIPresentationController(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UIPresentationControllerClass,_di_UIPresentationController>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUIPresentationController() { }
	
};


typedef void * PUIPresentationController;

__interface  INTERFACE_UUID("{37EEE7ED-E821-4A9E-95BD-BE37F187AC4F}") UIPopoverPresentationControllerClass  : public UIPresentationControllerClass 
{
	
};

__interface  INTERFACE_UUID("{DEFE6AF8-800B-47BD-A89A-03435C76B965}") UIPopoverPresentationController  : public UIPresentationController 
{
	HIDESBASE virtual void __cdecl setDelegate(void * delegate) = 0 ;
	HIDESBASE virtual void * __cdecl delegate() = 0 ;
	virtual void __cdecl setPermittedArrowDirections(unsigned long permittedArrowDirections) = 0 ;
	virtual unsigned long __cdecl permittedArrowDirections() = 0 ;
	virtual void __cdecl setSourceView(_di_UIView sourceView) = 0 ;
	virtual _di_UIView __cdecl sourceView() = 0 ;
	virtual void __cdecl setSourceRect(Iosapi::Foundation::NSRect sourceRect) = 0 ;
	virtual Iosapi::Foundation::NSRect __cdecl sourceRect() = 0 ;
	virtual void __cdecl setBarButtonItem(_di_UIBarButtonItem barButtonItem) = 0 ;
	virtual _di_UIBarButtonItem __cdecl barButtonItem() = 0 ;
	virtual unsigned long __cdecl arrowDirection() = 0 ;
	virtual void __cdecl setPassthroughViews(Iosapi::Foundation::_di_NSArray passthroughViews) = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl passthroughViews() = 0 ;
	virtual void __cdecl setBackgroundColor(_di_UIColor backgroundColor) = 0 ;
	virtual _di_UIColor __cdecl backgroundColor() = 0 ;
	virtual void __cdecl setPopoverLayoutMargins(UIEdgeInsets popoverLayoutMargins) = 0 ;
	virtual UIEdgeInsets __cdecl popoverLayoutMargins() = 0 ;
	virtual void __cdecl setPopoverBackgroundViewClass(void * popoverBackgroundViewClass) = 0 ;
	virtual void * __cdecl popoverBackgroundViewClass() = 0 ;
};

class PASCALIMPLEMENTATION TUIPopoverPresentationController : public Macapi::Objectivec::TOCGenericImport__2<_di_UIPopoverPresentationControllerClass,_di_UIPopoverPresentationController>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UIPopoverPresentationControllerClass,_di_UIPopoverPresentationController> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUIPopoverPresentationController(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UIPopoverPresentationControllerClass,_di_UIPopoverPresentationController>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUIPopoverPresentationController() { }
	
};


typedef void * PUIPopoverPresentationController;

__interface  INTERFACE_UUID("{957ECB39-51E4-4BD4-9BC1-79312E8D168A}") UIPrintPaperClass  : public Iosapi::Quartzcore::NSObjectClass 
{
	virtual void * __cdecl bestPaperForPageSize(Iosapi::Foundation::NSSize contentSize, Iosapi::Foundation::_di_NSArray withPapersFromArray) = 0 ;
};

__interface  INTERFACE_UUID("{9B023BF3-6850-4469-A902-CFDEAEA60EAB}") UIPrintPaper  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::NSSize __cdecl paperSize() = 0 ;
	virtual Iosapi::Foundation::NSRect __cdecl printRect() = 0 ;
	virtual Iosapi::Foundation::NSRect __cdecl printableRect() = 0 ;
};

class PASCALIMPLEMENTATION TUIPrintPaper : public Macapi::Objectivec::TOCGenericImport__2<_di_UIPrintPaperClass,_di_UIPrintPaper>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UIPrintPaperClass,_di_UIPrintPaper> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUIPrintPaper(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UIPrintPaperClass,_di_UIPrintPaper>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUIPrintPaper() { }
	
};


__interface  INTERFACE_UUID("{6D99085E-03D8-44DC-BDDD-2678A709CFD5}") UIPrintFormatterClass  : public Iosapi::Quartzcore::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{6F423EB0-4080-4B9F-AEFE-47E3CD5C6037}") UIPrintFormatter  : public Iosapi::Foundation::NSObject 
{
	virtual UIEdgeInsets __cdecl contentInsets() = 0 ;
	virtual void __cdecl drawInRect(Iosapi::Foundation::NSRect rect, long forPageAtIndex) = 0 ;
	virtual double __cdecl maximumContentHeight() = 0 ;
	virtual double __cdecl maximumContentWidth() = 0 ;
	virtual long __cdecl pageCount() = 0 ;
	virtual _di_UIPrintPageRenderer __cdecl printPageRenderer() = 0 ;
	virtual Iosapi::Foundation::NSRect __cdecl rectForPageAtIndex(long pageIndex) = 0 ;
	virtual void __cdecl removeFromPrintPageRenderer() = 0 ;
	virtual void __cdecl setContentInsets(UIEdgeInsets contentInsets) = 0 ;
	virtual void __cdecl setMaximumContentHeight(double maximumContentHeight) = 0 ;
	virtual void __cdecl setMaximumContentWidth(double maximumContentWidth) = 0 ;
	virtual void __cdecl setStartPage(long startPage) = 0 ;
	virtual long __cdecl startPage() = 0 ;
};

class PASCALIMPLEMENTATION TUIPrintFormatter : public Macapi::Objectivec::TOCGenericImport__2<_di_UIPrintFormatterClass,_di_UIPrintFormatter>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UIPrintFormatterClass,_di_UIPrintFormatter> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUIPrintFormatter(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UIPrintFormatterClass,_di_UIPrintFormatter>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUIPrintFormatter() { }
	
};


__interface  INTERFACE_UUID("{3ACDC1A9-123A-4BD7-A9D1-16E559B0F0AF}") UIPopoverControllerClass  : public Iosapi::Quartzcore::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{576C3F52-A469-434C-9BB0-01429C74E258}") UIPopoverController  : public Iosapi::Foundation::NSObject 
{
	virtual _di_UIViewController __cdecl contentViewController() = 0 ;
	virtual void * __cdecl delegate() = 0 ;
	virtual void __cdecl dismissPopoverAnimated(bool animated) = 0 ;
	virtual void * __cdecl initWithContentViewController(_di_UIViewController viewController) = 0 ;
	virtual bool __cdecl isPopoverVisible() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl passthroughViews() = 0 ;
	virtual unsigned long __cdecl popoverArrowDirection() = 0 ;
	virtual Iosapi::Foundation::NSSize __cdecl popoverContentSize() = 0 ;
	virtual UIEdgeInsets __cdecl popoverLayoutMargins() = 0 ;
	virtual void __cdecl presentPopoverFromBarButtonItem(_di_UIBarButtonItem item, unsigned long permittedArrowDirections, bool animated) = 0 ;
	virtual void __cdecl presentPopoverFromRect(Iosapi::Foundation::NSRect rect, _di_UIView inView, unsigned long permittedArrowDirections, bool animated) = 0 ;
	virtual void __cdecl setContentViewController(_di_UIViewController contentViewController) = 0 /* overload */;
	virtual void __cdecl setContentViewController(_di_UIViewController viewController, bool animated) = 0 /* overload */;
	virtual void __cdecl setDelegate(void * delegate) = 0 ;
	virtual void __cdecl setPassthroughViews(Iosapi::Foundation::_di_NSArray passthroughViews) = 0 ;
	virtual void __cdecl setPopoverBackgroundViewClass(void * popoverBackgroundViewClass) = 0 ;
	virtual void __cdecl setPopoverContentSize(Iosapi::Foundation::NSSize popoverContentSize) = 0 /* overload */;
	virtual void __cdecl setPopoverContentSize(Iosapi::Foundation::NSSize size, bool animated) = 0 /* overload */;
	virtual void __cdecl setPopoverLayoutMargins(UIEdgeInsets popoverLayoutMargins) = 0 ;
};

class PASCALIMPLEMENTATION TUIPopoverController : public Macapi::Objectivec::TOCGenericImport__2<_di_UIPopoverControllerClass,_di_UIPopoverController>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UIPopoverControllerClass,_di_UIPopoverController> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUIPopoverController(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UIPopoverControllerClass,_di_UIPopoverController>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUIPopoverController() { }
	
};


__interface  INTERFACE_UUID("{C8C6F374-BE00-4141-9E05-5E9ABA81D828}") UIPasteboardClass  : public Iosapi::Quartzcore::NSObjectClass 
{
	virtual void * __cdecl generalPasteboard() = 0 ;
	virtual void * __cdecl pasteboardWithName(Iosapi::Foundation::_di_NSString pasteboardName, bool create) = 0 ;
	virtual void * __cdecl pasteboardWithUniqueName() = 0 ;
	virtual void __cdecl removePasteboardWithName(Iosapi::Foundation::_di_NSString pasteboardName) = 0 ;
};

__interface  INTERFACE_UUID("{9B817EE3-BC7F-48BA-92E2-DA35D69F09CD}") UIPasteboard  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::_di_NSURL __cdecl URL() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl URLs() = 0 ;
	virtual void __cdecl addItems(Iosapi::Foundation::_di_NSArray items) = 0 ;
	virtual long __cdecl changeCount() = 0 ;
	virtual _di_UIColor __cdecl color() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl colors() = 0 ;
	virtual bool __cdecl containsPasteboardTypes(Iosapi::Foundation::_di_NSArray pasteboardTypes) = 0 /* overload */;
	virtual bool __cdecl containsPasteboardTypes(Iosapi::Foundation::_di_NSArray pasteboardTypes, Iosapi::Foundation::_di_NSIndexSet inItemSet) = 0 /* overload */;
	virtual Iosapi::Foundation::_di_NSData __cdecl dataForPasteboardType(Iosapi::Foundation::_di_NSString pasteboardType) = 0 /* overload */;
	virtual Iosapi::Foundation::_di_NSArray __cdecl dataForPasteboardType(Iosapi::Foundation::_di_NSString pasteboardType, Iosapi::Foundation::_di_NSIndexSet inItemSet) = 0 /* overload */;
	virtual void * __cdecl image() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl images() = 0 ;
	virtual bool __cdecl isPersistent() = 0 ;
	virtual Iosapi::Foundation::_di_NSIndexSet __cdecl itemSetWithPasteboardTypes(Iosapi::Foundation::_di_NSArray pasteboardTypes) = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl items() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl name() = 0 ;
	virtual long __cdecl numberOfItems() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl pasteboardTypes() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl pasteboardTypesForItemSet(Iosapi::Foundation::_di_NSIndexSet itemSet) = 0 ;
	virtual void __cdecl setColor(_di_UIColor color) = 0 ;
	virtual void __cdecl setColors(Iosapi::Foundation::_di_NSArray colors) = 0 ;
	virtual void __cdecl setData(Iosapi::Foundation::_di_NSData data, Iosapi::Foundation::_di_NSString forPasteboardType) = 0 ;
	virtual void __cdecl setImage(_di_UIImage image) = 0 ;
	virtual void __cdecl setImages(Iosapi::Foundation::_di_NSArray images) = 0 ;
	virtual void __cdecl setItems(Iosapi::Foundation::_di_NSArray items) = 0 ;
	virtual void __cdecl setPersistent(bool persistent) = 0 ;
	virtual void __cdecl setString(Iosapi::Foundation::_di_NSString string_) = 0 ;
	virtual void __cdecl setStrings(Iosapi::Foundation::_di_NSArray strings) = 0 ;
	virtual void __cdecl setURL(Iosapi::Foundation::_di_NSURL URL) = 0 ;
	virtual void __cdecl setURLs(Iosapi::Foundation::_di_NSArray URLs) = 0 ;
	virtual void __cdecl setValue(void * value, Iosapi::Foundation::_di_NSString forPasteboardType) = 0 ;
	virtual void * __cdecl string() = 0 ;
	virtual void * __cdecl strings() = 0 ;
	virtual void * __cdecl valueForPasteboardType(Iosapi::Foundation::_di_NSString pasteboardType) = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl valuesForPasteboardType(Iosapi::Foundation::_di_NSString pasteboardType, Iosapi::Foundation::_di_NSIndexSet inItemSet) = 0 ;
};

class PASCALIMPLEMENTATION TUIPasteboard : public Macapi::Objectivec::TOCGenericImport__2<_di_UIPasteboardClass,_di_UIPasteboard>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UIPasteboardClass,_di_UIPasteboard> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUIPasteboard(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UIPasteboardClass,_di_UIPasteboard>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUIPasteboard() { }
	
};


__interface  INTERFACE_UUID("{C53C376D-C495-4445-B4CF-89D5098A290C}") UILayoutGuide  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::NSRect __cdecl layoutFrame() = 0 ;
};

__interface  INTERFACE_UUID("{BC6ED940-E934-477F-AF6A-0249A5095935}") UIViewClass  : public UIResponderClass 
{
	virtual bool __cdecl areAnimationsEnabled() = 0 ;
	virtual void __cdecl beginAnimations(void * animationID, void * context) = 0 ;
	virtual void __cdecl commitAnimations() = 0 ;
	virtual void __cdecl setAnimationBeginsFromCurrentState(bool fromCurrentState) = 0 ;
	virtual void __cdecl setAnimationCurve(long curve) = 0 ;
	virtual void __cdecl setAnimationDelay(double delay) = 0 ;
	virtual void __cdecl setAnimationDelegate(void * delegate) = 0 ;
	virtual void __cdecl setAnimationDidStopSelector(void * selector) = 0 ;
	virtual void __cdecl setAnimationDuration(double duration) = 0 ;
	virtual void __cdecl setAnimationRepeatAutoreverses(bool repeatAutoreverses) = 0 ;
	virtual void __cdecl setAnimationRepeatCount(float repeatCount) = 0 ;
	virtual void __cdecl setAnimationStartDate(Iosapi::Foundation::_di_NSDate startDate) = 0 ;
	virtual void __cdecl setAnimationTransition(long transition, _di_UIView forView, bool cache) = 0 ;
	virtual void __cdecl setAnimationWillStartSelector(void * selector) = 0 ;
	virtual void __cdecl setAnimationsEnabled(bool enabled) = 0 ;
	virtual void __cdecl performWithoutAnimation(TUIKitAction actionsWithoutAnimation) = 0 ;
	virtual void __cdecl animateWithDurationDelayOptionsAnimationsCompletion(double duration, double delay, unsigned long options, TUIKitAction animations, TUIKitCompletion completion) = 0 ;
	virtual void __cdecl animateWithDurationAnimationsCompletion(double duration, TUIKitAction animations, TUIKitCompletion completion) = 0 ;
	virtual void __cdecl animateWithDurationAnimations(double duration, TUIKitAction animations) = 0 ;
	virtual void __cdecl animateWithDurationDelayUsingSpringWithDampingInitialSpringVelocityOptionsAnimationsCompletion(double duration, double delay, double usingSpringWithDamping, double initialSpringVelocity, unsigned long options, TUIKitAction animations, TUIKitCompletion completion) = 0 ;
	virtual void __cdecl transitionWithView(_di_UIView view, double duration, unsigned long options, TUIKitAction animations, TUIKitCompletion completion) = 0 ;
	virtual void __cdecl transitionFromView(_di_UIView fromView, _di_UIView toView, double duration, unsigned long options, TUIKitCompletion completion) = 0 ;
	virtual void __cdecl performSystemAnimation(unsigned long animation, Iosapi::Foundation::_di_NSArray onViews, unsigned long options, TUIKitAction animations, TUIKitCompletion completion) = 0 ;
	virtual void __cdecl animateKeyframesWithDuration(double duration, double delay, unsigned long options, TUIKitAction animations, TUIKitCompletion completion) = 0 ;
	virtual void __cdecl addKeyframeWithRelativeStartTime(double frameStartTime, double relativeDuration, TUIKitAction animations) = 0 ;
	virtual bool __cdecl requiresConstraintBasedLayout() = 0 ;
};

__interface  INTERFACE_UUID("{2DD827CB-85D2-4EE5-AA42-87941019F4B3}") UIView  : public UIResponder 
{
	virtual void __cdecl addGestureRecognizer(_di_UIGestureRecognizer gestureRecognizer) = 0 ;
	virtual void __cdecl addSubview(_di_UIView view) = 0 ;
	virtual void __cdecl addConstraint(_di_NSLayoutConstraint constraint) = 0 ;
	virtual void __cdecl addConstraints(Iosapi::Foundation::_di_NSArray constraints) = 0 ;
	virtual void __cdecl removeConstraint(_di_NSLayoutConstraint constraint) = 0 ;
	virtual void __cdecl removeConstraints(Iosapi::Foundation::_di_NSArray constraints) = 0 ;
	virtual void __cdecl updateConstraintsIfNeeded() = 0 ;
	virtual void __cdecl updateConstraints() = 0 ;
	virtual bool __cdecl needsUpdateConstraints() = 0 ;
	virtual void __cdecl setNeedsUpdateConstraints() = 0 ;
	virtual bool __cdecl translatesAutoresizingMaskIntoConstraints() = 0 ;
	virtual void __cdecl setTranslatesAutoresizingMaskIntoConstraints(bool flag) = 0 ;
	virtual double __cdecl alpha() = 0 ;
	virtual bool __cdecl autoresizesSubviews() = 0 ;
	virtual unsigned long __cdecl autoresizingMask() = 0 ;
	virtual _di_UIColor __cdecl backgroundColor() = 0 ;
	virtual Iosapi::Foundation::NSRect __cdecl bounds() = 0 ;
	virtual void __cdecl bringSubviewToFront(_di_UIView view) = 0 ;
	virtual Iosapi::Foundation::NSPoint __cdecl center() = 0 ;
	virtual bool __cdecl clearsContextBeforeDrawing() = 0 ;
	virtual bool __cdecl clipsToBounds() = 0 ;
	virtual long __cdecl contentMode() = 0 ;
	virtual double __cdecl contentScaleFactor() = 0 ;
	virtual Iosapi::Foundation::NSRect __cdecl contentStretch() = 0 ;
	virtual Iosapi::Foundation::NSPoint __cdecl convertPoint(Iosapi::Foundation::NSPoint point, _di_UIView fromView) = 0 /* overload */;
	virtual Iosapi::Foundation::NSPoint __cdecl convertPointToView(Iosapi::Foundation::NSPoint point, _di_UIView toView) = 0 /* overload */;
	virtual Iosapi::Foundation::NSRect __cdecl convertRect(Iosapi::Foundation::NSRect rect, _di_UIView fromView) = 0 /* overload */;
	virtual Iosapi::Foundation::_di_NSArray __cdecl constraints() = 0 ;
	virtual void __cdecl didAddSubview(_di_UIView subview) = 0 ;
	virtual void __cdecl didMoveToSuperview() = 0 ;
	virtual void __cdecl didMoveToWindow() = 0 ;
	virtual void __cdecl drawRect(Iosapi::Foundation::NSRect rect) = 0 /* overload */;
	virtual void __cdecl drawRect(Iosapi::Foundation::NSRect rect, _di_UIViewPrintFormatter forViewPrintFormatter) = 0 /* overload */;
	virtual void __cdecl drawViewHierarchyInRectAfterScreenUpdates(Iosapi::Foundation::NSRect rect, bool afterUpdates) = 0 ;
	virtual bool __cdecl endEditing(bool force) = 0 ;
	virtual void __cdecl exchangeSubviewAtIndex(long index1, long withSubviewAtIndex) = 0 ;
	virtual Iosapi::Foundation::NSRect __cdecl frame() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl gestureRecognizers() = 0 ;
	virtual bool __cdecl gestureRecognizerShouldBegin(_di_UIGestureRecognizer gestureRecognizer) = 0 ;
	virtual _di_UIView __cdecl hitTest(Iosapi::Foundation::NSPoint point, _di_UIEvent withEvent) = 0 ;
	virtual void * __cdecl initWithFrame(Iosapi::Foundation::NSRect frame) = 0 ;
	virtual void __cdecl insertSubview(_di_UIView view, _di_UIView aboveSubview) = 0 /* overload */;
	virtual void __cdecl insertSubview(_di_UIView view, long atIndex) = 0 /* overload */;
	virtual bool __cdecl isDescendantOfView(_di_UIView view) = 0 ;
	virtual bool __cdecl isExclusiveTouch() = 0 ;
	virtual bool __cdecl isHidden() = 0 ;
	virtual bool __cdecl isMultipleTouchEnabled() = 0 ;
	virtual bool __cdecl isOpaque() = 0 ;
	virtual bool __cdecl isUserInteractionEnabled() = 0 ;
	virtual Iosapi::Quartzcore::_di_CALayer __cdecl layer() = 0 ;
	virtual void __cdecl layoutIfNeeded() = 0 ;
	virtual void __cdecl layoutSubviews() = 0 ;
	virtual bool __cdecl pointInside(Iosapi::Foundation::NSPoint point, _di_UIEvent withEvent) = 0 ;
	virtual void __cdecl removeFromSuperview() = 0 ;
	virtual void __cdecl removeGestureRecognizer(_di_UIGestureRecognizer gestureRecognizer) = 0 ;
	virtual _di_UILayoutGuide __cdecl safeAreaLayoutGuide() = 0 ;
	virtual void __cdecl sendSubviewToBack(_di_UIView view) = 0 ;
	virtual void __cdecl setAlpha(double alpha) = 0 ;
	virtual void __cdecl setAutoresizesSubviews(bool autoresizesSubviews) = 0 ;
	virtual void __cdecl setAutoresizingMask(unsigned long autoresizingMask) = 0 ;
	virtual void __cdecl setBackgroundColor(_di_UIColor backgroundColor) = 0 ;
	virtual void __cdecl setBounds(Iosapi::Foundation::NSRect bounds) = 0 ;
	virtual void __cdecl setCenter(Iosapi::Foundation::NSPoint center) = 0 ;
	virtual void __cdecl setClearsContextBeforeDrawing(bool clearsContextBeforeDrawing) = 0 ;
	virtual void __cdecl setClipsToBounds(bool clipsToBounds) = 0 ;
	virtual void __cdecl setContentMode(long contentMode) = 0 ;
	virtual void __cdecl setContentScaleFactor(double contentScaleFactor) = 0 ;
	virtual void __cdecl setContentStretch(Iosapi::Foundation::NSRect contentStretch) = 0 ;
	virtual void __cdecl setExclusiveTouch(bool exclusiveTouch) = 0 ;
	virtual void __cdecl setFrame(Iosapi::Foundation::NSRect frame) = 0 ;
	virtual void __cdecl setGestureRecognizers(Iosapi::Foundation::_di_NSArray gestureRecognizers) = 0 ;
	virtual void __cdecl setHidden(bool hidden) = 0 ;
	virtual void __cdecl setMultipleTouchEnabled(bool multipleTouchEnabled) = 0 ;
	virtual void __cdecl setNeedsDisplay() = 0 ;
	virtual void __cdecl setNeedsDisplayInRect(Iosapi::Foundation::NSRect rect) = 0 ;
	virtual void __cdecl setNeedsLayout() = 0 ;
	virtual void __cdecl setOpaque(bool opaque) = 0 ;
	virtual void __cdecl setTag(long tag) = 0 ;
	virtual void __cdecl setTransform(Iosapi::Coregraphics::CGAffineTransform transform) = 0 ;
	virtual void __cdecl setTintColor(_di_UIColor color) = 0 ;
	virtual void __cdecl setUserInteractionEnabled(bool userInteractionEnabled) = 0 ;
	virtual Iosapi::Foundation::NSSize __cdecl sizeThatFits(Iosapi::Foundation::NSSize size) = 0 ;
	virtual void __cdecl sizeToFit() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl subviews() = 0 ;
	virtual void * __cdecl superview() = 0 ;
	virtual long __cdecl tag() = 0 ;
	virtual Iosapi::Coregraphics::CGAffineTransform __cdecl transform() = 0 ;
	virtual _di_UIColor __cdecl tintColor() = 0 ;
	virtual _di_UIViewPrintFormatter __cdecl viewPrintFormatter() = 0 ;
	virtual _di_UIView __cdecl viewWithTag(long tag) = 0 ;
	virtual void __cdecl willMoveToSuperview(_di_UIView newSuperview) = 0 ;
	virtual void __cdecl willMoveToWindow(_di_UIWindow newWindow) = 0 ;
	virtual void __cdecl willRemoveSubview(_di_UIView subview) = 0 ;
	virtual _di_UIWindow __cdecl window() = 0 ;
};

class PASCALIMPLEMENTATION TUIView : public Macapi::Objectivec::TOCGenericImport__2<_di_UIViewClass,_di_UIView>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UIViewClass,_di_UIView> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUIView(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UIViewClass,_di_UIView>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUIView() { }
	
};


__interface  INTERFACE_UUID("{9FEB4EF1-7FBA-4325-B771-330FEDA416C5}") UIPrinterClass  : public Iosapi::Quartzcore::NSObjectClass 
{
	virtual _di_UIPrinter __cdecl printerWithURL(Iosapi::Foundation::_di_NSURL url) = 0 ;
};

__interface  INTERFACE_UUID("{FA556E28-1622-43AD-9B23-7133D5245612}") UIPrinter  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::_di_NSURL __cdecl url() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl displayName() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl displayLocation() = 0 ;
	virtual long __cdecl supportedJobTypes() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl makeAndModel() = 0 ;
	virtual bool __cdecl supportsColor() = 0 ;
	virtual bool __cdecl supportsDuplex() = 0 ;
	virtual void __cdecl contactPrinter(TUIKitCompletion completionHandler) = 0 ;
};

class PASCALIMPLEMENTATION TUIPrinter : public Macapi::Objectivec::TOCGenericImport__2<_di_UIPrinterClass,_di_UIPrinter>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UIPrinterClass,_di_UIPrinter> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUIPrinter(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UIPrinterClass,_di_UIPrinter>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUIPrinter() { }
	
};


typedef void * PUIPrinter;

__interface  INTERFACE_UUID("{D1F8498A-BEEC-4DCF-909C-44E66A0BDDBC}") UIPrinterPickerControllerClass  : public Iosapi::Quartzcore::NSObjectClass 
{
	virtual _di_UIPrinterPickerController __cdecl printerPickerControllerWithInitiallySelectedPrinter(_di_UIPrinter printer) = 0 ;
};

__interface  INTERFACE_UUID("{65BFCAC6-5146-4FFD-9A95-6AE4CF2B8F8C}") UIPrinterPickerController  : public Iosapi::Foundation::NSObject 
{
	virtual _di_UIPrinter __cdecl selectedPrinter() = 0 ;
	virtual void __cdecl setDelegate(void * delegate) = 0 ;
	virtual void * __cdecl delegate() = 0 ;
	virtual bool __cdecl presentAnimated(bool animated, UIPrinterPickerCompletionHandler completionHandler) = 0 ;
	virtual bool __cdecl presentFromRect(Iosapi::Foundation::NSRect rect, _di_UIView inView, bool animated, UIPrinterPickerCompletionHandler completionHandler) = 0 ;
	virtual bool __cdecl presentFromBarButtonItem(_di_UIBarButtonItem item, bool animated, UIPrinterPickerCompletionHandler completionHandler) = 0 ;
	virtual void __cdecl dismissAnimated(bool animated) = 0 ;
};

class PASCALIMPLEMENTATION TUIPrinterPickerController : public Macapi::Objectivec::TOCGenericImport__2<_di_UIPrinterPickerControllerClass,_di_UIPrinterPickerController>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UIPrinterPickerControllerClass,_di_UIPrinterPickerController> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUIPrinterPickerController(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UIPrinterPickerControllerClass,_di_UIPrinterPickerController>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUIPrinterPickerController() { }
	
};


typedef void * PUIPrinterPickerController;

__interface  INTERFACE_UUID("{96A50B8F-2F32-4D42-AAF1-29DE9C2F98CD}") UIPrintPageRendererClass  : public Iosapi::Quartzcore::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{4E75D23D-3D4E-44B3-BF58-CCB68F0AD584}") UIPrintPageRenderer  : public Iosapi::Foundation::NSObject 
{
	virtual void __cdecl addPrintFormatter(_di_UIPrintFormatter formatter, long startingAtPageAtIndex) = 0 ;
	virtual void __cdecl drawContentForPageAtIndex(long pageIndex, Iosapi::Foundation::NSRect inRect) = 0 ;
	virtual void __cdecl drawFooterForPageAtIndex(long pageIndex, Iosapi::Foundation::NSRect inRect) = 0 ;
	virtual void __cdecl drawHeaderForPageAtIndex(long pageIndex, Iosapi::Foundation::NSRect inRect) = 0 ;
	virtual void __cdecl drawPageAtIndex(long pageIndex, Iosapi::Foundation::NSRect inRect) = 0 ;
	virtual void __cdecl drawPrintFormatter(_di_UIPrintFormatter printFormatter, long forPageAtIndex) = 0 ;
	virtual double __cdecl footerHeight() = 0 ;
	virtual double __cdecl headerHeight() = 0 ;
	virtual long __cdecl numberOfPages() = 0 ;
	virtual Iosapi::Foundation::NSRect __cdecl paperRect() = 0 ;
	virtual void __cdecl prepareForDrawingPages(Iosapi::Foundation::NSRange range) = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl printFormatters() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl printFormattersForPageAtIndex(long pageIndex) = 0 ;
	virtual Iosapi::Foundation::NSRect __cdecl printableRect() = 0 ;
	virtual void __cdecl setFooterHeight(double footerHeight) = 0 ;
	virtual void __cdecl setHeaderHeight(double headerHeight) = 0 ;
	virtual void __cdecl setPrintFormatters(Iosapi::Foundation::_di_NSArray printFormatters) = 0 ;
};

class PASCALIMPLEMENTATION TUIPrintPageRenderer : public Macapi::Objectivec::TOCGenericImport__2<_di_UIPrintPageRendererClass,_di_UIPrintPageRenderer>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UIPrintPageRendererClass,_di_UIPrintPageRenderer> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUIPrintPageRenderer(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UIPrintPageRendererClass,_di_UIPrintPageRenderer>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUIPrintPageRenderer() { }
	
};


__interface  INTERFACE_UUID("{D3566B82-3014-40C6-B7E3-DFC22AF39319}") UIPrintInteractionControllerClass  : public Iosapi::Quartzcore::NSObjectClass 
{
	virtual bool __cdecl canPrintData(Iosapi::Foundation::_di_NSData data) = 0 ;
	virtual bool __cdecl canPrintURL(Iosapi::Foundation::_di_NSURL url) = 0 ;
	virtual bool __cdecl isPrintingAvailable() = 0 ;
	virtual Iosapi::Foundation::_di_NSSet __cdecl printableUTIs() = 0 ;
	virtual void * __cdecl sharedPrintController() = 0 ;
};

__interface  INTERFACE_UUID("{0FEF6AA7-132B-41C8-BB12-045C43027D4B}") UIPrintInteractionController  : public Iosapi::Foundation::NSObject 
{
	virtual void * __cdecl delegate() = 0 ;
	virtual void __cdecl dismissAnimated(bool animated) = 0 ;
	virtual _di_UIPrintFormatter __cdecl printFormatter() = 0 ;
	virtual _di_UIPrintInfo __cdecl printInfo() = 0 ;
	virtual _di_UIPrintPageRenderer __cdecl printPageRenderer() = 0 ;
	virtual _di_UIPrintPaper __cdecl printPaper() = 0 ;
	virtual void * __cdecl printingItem() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl printingItems() = 0 ;
	virtual void __cdecl setDelegate(void * delegate) = 0 ;
	virtual void __cdecl setPrintFormatter(_di_UIPrintFormatter printFormatter) = 0 ;
	virtual void __cdecl setPrintInfo(_di_UIPrintInfo printInfo) = 0 ;
	virtual void __cdecl setPrintPageRenderer(_di_UIPrintPageRenderer printPageRenderer) = 0 ;
	virtual void __cdecl setPrintingItem(void * printingItem) = 0 ;
	virtual void __cdecl setPrintingItems(Iosapi::Foundation::_di_NSArray printingItems) = 0 ;
	virtual void __cdecl setShowsPageRange(bool showsPageRange) = 0 ;
	virtual bool __cdecl showsPageRange() = 0 ;
};

class PASCALIMPLEMENTATION TUIPrintInteractionController : public Macapi::Objectivec::TOCGenericImport__2<_di_UIPrintInteractionControllerClass,_di_UIPrintInteractionController>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UIPrintInteractionControllerClass,_di_UIPrintInteractionController> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUIPrintInteractionController(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UIPrintInteractionControllerClass,_di_UIPrintInteractionController>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUIPrintInteractionController() { }
	
};


__interface  INTERFACE_UUID("{876A42C5-4D35-4DB0-BAC8-588C41A607A2}") UIPrintInfoClass  : public Iosapi::Quartzcore::NSObjectClass 
{
	virtual void * __cdecl printInfo() = 0 ;
	virtual void * __cdecl printInfoWithDictionary(Iosapi::Foundation::_di_NSDictionary dictionary) = 0 ;
};

__interface  INTERFACE_UUID("{8628D24C-6D8D-4AA1-AF59-EE0C648DC9EF}") UIPrintInfo  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::_di_NSDictionary __cdecl dictionaryRepresentation() = 0 ;
	virtual long __cdecl duplex() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl jobName() = 0 ;
	virtual long __cdecl orientation() = 0 ;
	virtual long __cdecl outputType() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl printerID() = 0 ;
	virtual void __cdecl setDuplex(long duplex) = 0 ;
	virtual void __cdecl setJobName(Iosapi::Foundation::_di_NSString jobName) = 0 ;
	virtual void __cdecl setOrientation(long orientation) = 0 ;
	virtual void __cdecl setOutputType(long outputType) = 0 ;
	virtual void __cdecl setPrinterID(Iosapi::Foundation::_di_NSString printerID) = 0 ;
};

class PASCALIMPLEMENTATION TUIPrintInfo : public Macapi::Objectivec::TOCGenericImport__2<_di_UIPrintInfoClass,_di_UIPrintInfo>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UIPrintInfoClass,_di_UIPrintInfo> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUIPrintInfo(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UIPrintInfoClass,_di_UIPrintInfo>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUIPrintInfo() { }
	
};


__interface  INTERFACE_UUID("{B56F6316-68B0-4B43-9A83-9D440AB07D83}") UIBarItemClass  : public Iosapi::Quartzcore::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{D2F7FB4F-12F3-41E4-8051-4252C65443D7}") UIBarItem  : public Iosapi::Foundation::NSObject 
{
	virtual _di_UIImage __cdecl image() = 0 ;
	virtual UIEdgeInsets __cdecl imageInsets() = 0 ;
	virtual bool __cdecl isEnabled() = 0 ;
	virtual _di_UIImage __cdecl landscapeImagePhone() = 0 ;
	virtual UIEdgeInsets __cdecl landscapeImagePhoneInsets() = 0 ;
	virtual void __cdecl setEnabled(bool enabled) = 0 ;
	virtual void __cdecl setImage(_di_UIImage image) = 0 ;
	virtual void __cdecl setImageInsets(UIEdgeInsets imageInsets) = 0 ;
	virtual void __cdecl setLandscapeImagePhone(_di_UIImage landscapeImagePhone) = 0 ;
	virtual void __cdecl setLandscapeImagePhoneInsets(UIEdgeInsets landscapeImagePhoneInsets) = 0 ;
	virtual void __cdecl setTag(long tag) = 0 ;
	virtual void __cdecl setTitle(Iosapi::Foundation::_di_NSString title) = 0 ;
	virtual void __cdecl setTitleTextAttributes(Iosapi::Foundation::_di_NSDictionary attributes, unsigned long forState) = 0 ;
	virtual long __cdecl tag() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl title() = 0 ;
	virtual Iosapi::Foundation::_di_NSDictionary __cdecl titleTextAttributesForState(unsigned long state) = 0 ;
};

class PASCALIMPLEMENTATION TUIBarItem : public Macapi::Objectivec::TOCGenericImport__2<_di_UIBarItemClass,_di_UIBarItem>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UIBarItemClass,_di_UIBarItem> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUIBarItem(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UIBarItemClass,_di_UIBarItem>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUIBarItem() { }
	
};


__interface  INTERFACE_UUID("{471808BD-D532-44FE-9FAE-2F271EDBF91C}") UIBezierPathClass  : public Iosapi::Quartzcore::NSObjectClass 
{
	virtual void * __cdecl bezierPath() = 0 ;
	virtual void * __cdecl bezierPathWithArcCenter(Iosapi::Foundation::NSPoint center, double radius, double startAngle, double endAngle, bool clockwise) = 0 ;
	virtual void * __cdecl bezierPathWithCGPath(void * CGPath) = 0 ;
	virtual void * __cdecl bezierPathWithOvalInRect(Iosapi::Foundation::NSRect rect) = 0 ;
	virtual void * __cdecl bezierPathWithRect(Iosapi::Foundation::NSRect rect) = 0 ;
	virtual void * __cdecl bezierPathWithRoundedRect(Iosapi::Foundation::NSRect rect, unsigned long byRoundingCorners, Iosapi::Foundation::NSSize cornerRadii) = 0 /* overload */;
	virtual void * __cdecl bezierPathWithRoundedRect(Iosapi::Foundation::NSRect rect, double cornerRadius) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{1C09BF52-8B2B-4EAE-8F63-3C88754FB694}") UIBezierPath  : public Iosapi::Foundation::NSObject 
{
	virtual void * __cdecl CGPath() = 0 ;
	virtual void __cdecl addArcWithCenter(Iosapi::Foundation::NSPoint center, double radius, double startAngle, double endAngle, bool clockwise) = 0 ;
	virtual void __cdecl addClip() = 0 ;
	virtual void __cdecl addCurveToPoint(Iosapi::Foundation::NSPoint endPoint, Iosapi::Foundation::NSPoint controlPoint1, Iosapi::Foundation::NSPoint controlPoint2) = 0 ;
	virtual void __cdecl addLineToPoint(Iosapi::Foundation::NSPoint point) = 0 ;
	virtual void __cdecl addQuadCurveToPoint(Iosapi::Foundation::NSPoint endPoint, Iosapi::Foundation::NSPoint controlPoint) = 0 ;
	virtual void __cdecl appendPath(_di_UIBezierPath bezierPath) = 0 ;
	virtual void __cdecl applyTransform(Iosapi::Coregraphics::CGAffineTransform transform) = 0 ;
	virtual Iosapi::Foundation::NSRect __cdecl bounds() = 0 ;
	virtual void __cdecl closePath() = 0 ;
	virtual bool __cdecl containsPoint(Iosapi::Foundation::NSPoint point) = 0 ;
	virtual Iosapi::Foundation::NSPoint __cdecl currentPoint() = 0 ;
	virtual void __cdecl fill() = 0 ;
	virtual void __cdecl fillWithBlendMode(unsigned blendMode, double alpha) = 0 ;
	virtual double __cdecl flatness() = 0 ;
	virtual void __cdecl getLineDash(Iosapi::Cocoatypes::PCGFloat pattern, long count, Iosapi::Cocoatypes::PCGFloat phase) = 0 ;
	virtual bool __cdecl isEmpty() = 0 ;
	virtual unsigned __cdecl lineCapStyle() = 0 ;
	virtual unsigned __cdecl lineJoinStyle() = 0 ;
	virtual double __cdecl lineWidth() = 0 ;
	virtual double __cdecl miterLimit() = 0 ;
	virtual void __cdecl moveToPoint(Iosapi::Foundation::NSPoint point) = 0 ;
	virtual void __cdecl removeAllPoints() = 0 ;
	virtual void __cdecl setCGPath(void * CGPath) = 0 ;
	virtual void __cdecl setFlatness(double flatness) = 0 ;
	virtual void __cdecl setLineCapStyle(unsigned lineCapStyle) = 0 ;
	virtual void __cdecl setLineDash(Iosapi::Cocoatypes::PCGFloat pattern, long count, double phase) = 0 ;
	virtual void __cdecl setLineJoinStyle(unsigned lineJoinStyle) = 0 ;
	virtual void __cdecl setLineWidth(double lineWidth) = 0 ;
	virtual void __cdecl setMiterLimit(double miterLimit) = 0 ;
	virtual void __cdecl setUsesEvenOddFillRule(bool usesEvenOddFillRule) = 0 ;
	virtual void __cdecl stroke() = 0 ;
	virtual void __cdecl strokeWithBlendMode(unsigned blendMode, double alpha) = 0 ;
	virtual bool __cdecl usesEvenOddFillRule() = 0 ;
};

class PASCALIMPLEMENTATION TUIBezierPath : public Macapi::Objectivec::TOCGenericImport__2<_di_UIBezierPathClass,_di_UIBezierPath>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UIBezierPathClass,_di_UIBezierPath> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUIBezierPath(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UIBezierPathClass,_di_UIBezierPath>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUIBezierPath() { }
	
};


__interface  INTERFACE_UUID("{AC93733E-E033-4450-BC5D-8FDF69EFECA8}") UIAccessibilityElementClass  : public Iosapi::Quartzcore::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{EE478997-636B-41A8-85EB-C3076B37D01B}") UIAccessibilityElement  : public Iosapi::Foundation::NSObject 
{
	virtual void * __cdecl accessibilityContainer() = 0 ;
	virtual Iosapi::Foundation::NSRect __cdecl accessibilityFrame() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl accessibilityHint() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl accessibilityLabel() = 0 ;
	virtual unsigned __int64 __cdecl accessibilityTraits() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl accessibilityValue() = 0 ;
	virtual void * __cdecl initWithAccessibilityContainer(void * container) = 0 ;
	virtual bool __cdecl isAccessibilityElement() = 0 ;
	virtual void __cdecl setAccessibilityContainer(void * accessibilityContainer) = 0 ;
	virtual void __cdecl setAccessibilityFrame(Iosapi::Foundation::NSRect accessibilityFrame) = 0 ;
	virtual void __cdecl setAccessibilityHint(Iosapi::Foundation::_di_NSString accessibilityHint) = 0 ;
	virtual void __cdecl setAccessibilityLabel(Iosapi::Foundation::_di_NSString accessibilityLabel) = 0 ;
	virtual void __cdecl setAccessibilityTraits(unsigned __int64 accessibilityTraits) = 0 ;
	virtual void __cdecl setAccessibilityValue(Iosapi::Foundation::_di_NSString accessibilityValue) = 0 ;
	virtual void __cdecl setIsAccessibilityElement(bool isAccessibilityElement) = 0 ;
};

class PASCALIMPLEMENTATION TUIAccessibilityElement : public Macapi::Objectivec::TOCGenericImport__2<_di_UIAccessibilityElementClass,_di_UIAccessibilityElement>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UIAccessibilityElementClass,_di_UIAccessibilityElement> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUIAccessibilityElement(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UIAccessibilityElementClass,_di_UIAccessibilityElement>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUIAccessibilityElement() { }
	
};


__interface  INTERFACE_UUID("{88FA2AAF-47F1-44E6-AE56-E2D172B76C7F}") UIAccelerationClass  : public Iosapi::Quartzcore::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{707BFB31-03FF-4258-912B-D963C644225C}") UIAcceleration  : public Iosapi::Foundation::NSObject 
{
	virtual double __cdecl timestamp() = 0 ;
	virtual double __cdecl x() = 0 ;
	virtual double __cdecl y() = 0 ;
	virtual double __cdecl z() = 0 ;
};

class PASCALIMPLEMENTATION TUIAcceleration : public Macapi::Objectivec::TOCGenericImport__2<_di_UIAccelerationClass,_di_UIAcceleration>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UIAccelerationClass,_di_UIAcceleration> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUIAcceleration(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UIAccelerationClass,_di_UIAcceleration>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUIAcceleration() { }
	
};


__interface  INTERFACE_UUID("{D63171CF-FA0D-452B-801B-90B217F442B2}") UIAccelerometerClass  : public Iosapi::Quartzcore::NSObjectClass 
{
	virtual void * __cdecl sharedAccelerometer() = 0 ;
};

__interface  INTERFACE_UUID("{87EEFC83-5AE2-451E-AC08-3E2E675A8073}") UIAccelerometer  : public Iosapi::Foundation::NSObject 
{
	virtual void * __cdecl delegate() = 0 ;
	virtual void __cdecl setDelegate(void * delegate) = 0 ;
	virtual void __cdecl setUpdateInterval(double updateInterval) = 0 ;
	virtual double __cdecl updateInterval() = 0 ;
};

class PASCALIMPLEMENTATION TUIAccelerometer : public Macapi::Objectivec::TOCGenericImport__2<_di_UIAccelerometerClass,_di_UIAccelerometer>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UIAccelerometerClass,_di_UIAccelerometer> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUIAccelerometer(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UIAccelerometerClass,_di_UIAccelerometer>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUIAccelerometer() { }
	
};


__interface  INTERFACE_UUID("{874EBFF8-FF0E-4298-8E11-EAC567414FAB}") UIDeviceClass  : public Iosapi::Quartzcore::NSObjectClass 
{
	virtual void * __cdecl currentDevice() = 0 ;
};

__interface  INTERFACE_UUID("{94056B60-4607-4AB2-B515-545041F12526}") UIDevice  : public Iosapi::Foundation::NSObject 
{
	virtual float __cdecl batteryLevel() = 0 ;
	virtual long __cdecl batteryState() = 0 ;
	virtual void __cdecl beginGeneratingDeviceOrientationNotifications() = 0 ;
	virtual void __cdecl endGeneratingDeviceOrientationNotifications() = 0 ;
	virtual bool __cdecl isBatteryMonitoringEnabled() = 0 ;
	virtual bool __cdecl isGeneratingDeviceOrientationNotifications() = 0 ;
	virtual bool __cdecl isMultitaskingSupported() = 0 ;
	virtual bool __cdecl isProximityMonitoringEnabled() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl localizedModel() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl model() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl name() = 0 ;
	virtual long __cdecl orientation() = 0 ;
	virtual void __cdecl playInputClick() = 0 ;
	virtual bool __cdecl proximityState() = 0 ;
	virtual void __cdecl setBatteryMonitoringEnabled(bool batteryMonitoringEnabled) = 0 ;
	virtual void __cdecl setProximityMonitoringEnabled(bool proximityMonitoringEnabled) = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl systemName() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl systemVersion() = 0 ;
	virtual long __cdecl userInterfaceIdiom() = 0 ;
	virtual Iosapi::Foundation::_di_NSUUID __cdecl identifierForVendor() = 0 ;
};

class PASCALIMPLEMENTATION TUIDevice : public Macapi::Objectivec::TOCGenericImport__2<_di_UIDeviceClass,_di_UIDevice>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UIDeviceClass,_di_UIDevice> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUIDevice(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UIDeviceClass,_di_UIDevice>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUIDevice() { }
	
};


__interface  INTERFACE_UUID("{59DB4449-CE47-4FBE-8DBC-D979ADEA4832}") UIDocumentClass  : public Iosapi::Quartzcore::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{FF4EE4EC-E153-426F-A000-30DD3297CC55}") UIDocument  : public Iosapi::Foundation::NSObject 
{
	virtual void * __cdecl changeCountTokenForSaveOperation(long saveOperation) = 0 ;
	virtual void * __cdecl contentsForType(Iosapi::Foundation::_di_NSString typeName, Iosapi::Foundation::_di_NSError error) = 0 ;
	virtual void __cdecl disableEditing() = 0 ;
	virtual unsigned long __cdecl documentState() = 0 ;
	virtual void __cdecl enableEditing() = 0 ;
	virtual Iosapi::Foundation::_di_NSDictionary __cdecl fileAttributesToWriteToURL(Iosapi::Foundation::_di_NSURL url, long forSaveOperation, Iosapi::Foundation::_di_NSError error) = 0 ;
	virtual Iosapi::Foundation::_di_NSDate __cdecl fileModificationDate() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl fileNameExtensionForType(Iosapi::Foundation::_di_NSString typeName, long saveOperation) = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl fileType() = 0 ;
	virtual Iosapi::Foundation::_di_NSURL __cdecl fileURL() = 0 ;
	virtual void __cdecl finishedHandlingError(Iosapi::Foundation::_di_NSError error, bool recovered) = 0 ;
	virtual void __cdecl handleError(Iosapi::Foundation::_di_NSError error, bool userInteractionPermitted) = 0 ;
	virtual bool __cdecl hasUnsavedChanges() = 0 ;
	virtual void * __cdecl initWithFileURL(Iosapi::Foundation::_di_NSURL url) = 0 ;
	virtual bool __cdecl loadFromContents(void * contents, Iosapi::Foundation::_di_NSString ofType, Iosapi::Foundation::_di_NSError error) = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl localizedName() = 0 ;
	virtual bool __cdecl readFromURL(Iosapi::Foundation::_di_NSURL url, Iosapi::Foundation::_di_NSError error) = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl savingFileType() = 0 ;
	virtual void __cdecl setFileModificationDate(Iosapi::Foundation::_di_NSDate fileModificationDate) = 0 ;
	virtual void __cdecl setUndoManager(Iosapi::Foundation::_di_NSUndoManager undoManager) = 0 ;
	virtual Iosapi::Foundation::_di_NSUndoManager __cdecl undoManager() = 0 ;
	virtual void __cdecl updateChangeCount(long change) = 0 ;
	virtual void __cdecl updateChangeCountWithToken(void * changeCountToken, long forSaveOperation) = 0 ;
	virtual void __cdecl userInteractionNoLongerPermittedForError(Iosapi::Foundation::_di_NSError error) = 0 ;
	virtual bool __cdecl writeContents(void * contents, Iosapi::Foundation::_di_NSDictionary andAttributes, Iosapi::Foundation::_di_NSURL safelyToURL, long forSaveOperation, Iosapi::Foundation::_di_NSError error) = 0 /* overload */;
	virtual bool __cdecl writeContents(void * contents, Iosapi::Foundation::_di_NSURL toURL, long forSaveOperation, Iosapi::Foundation::_di_NSURL originalContentsURL, Iosapi::Foundation::_di_NSError error) = 0 /* overload */;
};

class PASCALIMPLEMENTATION TUIDocument : public Macapi::Objectivec::TOCGenericImport__2<_di_UIDocumentClass,_di_UIDocument>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UIDocumentClass,_di_UIDocument> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUIDocument(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UIDocumentClass,_di_UIDocument>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUIDocument() { }
	
};


__interface  INTERFACE_UUID("{880C5B3F-C073-42B1-8C9D-8A6B70945125}") UIEventClass  : public Iosapi::Quartzcore::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{EEA6BDEF-5C24-4E2A-A1C7-9206864D0B2F}") UIEvent  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::_di_NSSet __cdecl allTouches() = 0 ;
	virtual long __cdecl subtype() = 0 ;
	virtual double __cdecl timestamp() = 0 ;
	virtual Iosapi::Foundation::_di_NSSet __cdecl touchesForGestureRecognizer(_di_UIGestureRecognizer gesture) = 0 ;
	virtual Iosapi::Foundation::_di_NSSet __cdecl touchesForView(_di_UIView view) = 0 ;
	virtual Iosapi::Foundation::_di_NSSet __cdecl touchesForWindow(_di_UIWindow window) = 0 ;
};

class PASCALIMPLEMENTATION TUIEvent : public Macapi::Objectivec::TOCGenericImport__2<_di_UIEventClass,_di_UIEvent>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UIEventClass,_di_UIEvent> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUIEvent(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UIEventClass,_di_UIEvent>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUIEvent() { }
	
};


__interface  INTERFACE_UUID("{1AEC1ED2-F0F1-4D18-8044-F7529842F28A}") UIDocumentInteractionControllerClass  : public Iosapi::Quartzcore::NSObjectClass 
{
	virtual void * __cdecl interactionControllerWithURL(Iosapi::Foundation::_di_NSURL url) = 0 ;
};

__interface  INTERFACE_UUID("{CCDBD0CE-D6B9-4D2B-A2F3-66F6F722B8D4}") UIDocumentInteractionController  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::_di_NSURL __cdecl URL() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl UTI() = 0 ;
	virtual void * __cdecl annotation() = 0 ;
	virtual void * __cdecl delegate() = 0 ;
	virtual void __cdecl dismissMenuAnimated(bool animated) = 0 ;
	virtual void __cdecl dismissPreviewAnimated(bool animated) = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl gestureRecognizers() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl icons() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl name() = 0 ;
	virtual bool __cdecl presentOpenInMenuFromBarButtonItem(_di_UIBarButtonItem item, bool animated) = 0 ;
	virtual bool __cdecl presentOpenInMenuFromRect(Iosapi::Foundation::NSRect rect, _di_UIView inView, bool animated) = 0 ;
	virtual bool __cdecl presentOptionsMenuFromBarButtonItem(_di_UIBarButtonItem item, bool animated) = 0 ;
	virtual bool __cdecl presentOptionsMenuFromRect(Iosapi::Foundation::NSRect rect, _di_UIView inView, bool animated) = 0 ;
	virtual bool __cdecl presentPreviewAnimated(bool animated) = 0 ;
	virtual void __cdecl setAnnotation(void * annotation) = 0 ;
	virtual void __cdecl setDelegate(void * delegate) = 0 ;
	virtual void __cdecl setName(Iosapi::Foundation::_di_NSString name) = 0 ;
	virtual void __cdecl setURL(Iosapi::Foundation::_di_NSURL URL) = 0 ;
	virtual void __cdecl setUTI(Iosapi::Foundation::_di_NSString UTI) = 0 ;
};

class PASCALIMPLEMENTATION TUIDocumentInteractionController : public Macapi::Objectivec::TOCGenericImport__2<_di_UIDocumentInteractionControllerClass,_di_UIDocumentInteractionController>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UIDocumentInteractionControllerClass,_di_UIDocumentInteractionController> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUIDocumentInteractionController(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UIDocumentInteractionControllerClass,_di_UIDocumentInteractionController>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUIDocumentInteractionController() { }
	
};


__interface  INTERFACE_UUID("{E0AE4AE6-6490-450C-87AB-9F2BCE1A6F45}") UITouchClass  : public Iosapi::Quartzcore::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{990DEAF7-4A0D-4AEE-9D91-BA9EAC3331AD}") UITouch  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::_di_NSArray __cdecl gestureRecognizers() = 0 ;
	virtual Iosapi::Foundation::NSPoint __cdecl locationInView(_di_UIView view) = 0 ;
	virtual long __cdecl phase() = 0 ;
	virtual Iosapi::Foundation::NSPoint __cdecl previousLocationInView(_di_UIView view) = 0 ;
	virtual unsigned long __cdecl tapCount() = 0 ;
	virtual double __cdecl timestamp() = 0 ;
	virtual _di_UIView __cdecl view() = 0 ;
	virtual _di_UIWindow __cdecl window() = 0 ;
};

class PASCALIMPLEMENTATION TUITouch : public Macapi::Objectivec::TOCGenericImport__2<_di_UITouchClass,_di_UITouch>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UITouchClass,_di_UITouch> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUITouch(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UITouchClass,_di_UITouch>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUITouch() { }
	
};


__interface  INTERFACE_UUID("{F3401533-7644-473A-9562-AC8485414C10}") UIColorClass  : public Iosapi::Quartzcore::NSObjectClass 
{
	virtual void * __cdecl blackColor() = 0 ;
	virtual void * __cdecl blueColor() = 0 ;
	virtual void * __cdecl brownColor() = 0 ;
	virtual void * __cdecl clearColor() = 0 ;
	virtual void * __cdecl colorNamed(Iosapi::Foundation::_di_NSString name) = 0 /* overload */;
	virtual void * __cdecl colorNamed(Iosapi::Foundation::_di_NSString name, Iosapi::Foundation::_di_NSBundle bundle, _di_UITraitCollection traitCollection) = 0 /* overload */;
	virtual void * __cdecl colorWithCGColor(void * cgColor) = 0 ;
	virtual void * __cdecl colorWithCIColor(Iosapi::Coreimage::_di_CIColor ciColor) = 0 ;
	virtual void * __cdecl colorWithDisplayP3Red(double displayP3Red, double green, double blue, double alpha) = 0 ;
	virtual void * __cdecl colorWithHue(double hue, double saturation, double brightness, double alpha) = 0 ;
	virtual void * __cdecl colorWithPatternImage(_di_UIImage image) = 0 ;
	virtual void * __cdecl colorWithRed(double red, double green, double blue, double alpha) = 0 ;
	virtual void * __cdecl colorWithWhite(double white, double alpha) = 0 ;
	virtual void * __cdecl cyanColor() = 0 ;
	virtual void * __cdecl darkGrayColor() = 0 ;
	virtual void * __cdecl darkTextColor() = 0 ;
	virtual void * __cdecl grayColor() = 0 ;
	virtual void * __cdecl greenColor() = 0 ;
	virtual void * __cdecl groupTableViewBackgroundColor() = 0 ;
	virtual void * __cdecl labelColor() = 0 ;
	virtual void * __cdecl lightGrayColor() = 0 ;
	virtual void * __cdecl lightTextColor() = 0 ;
	virtual void * __cdecl linkColor() = 0 ;
	virtual void * __cdecl magentaColor() = 0 ;
	virtual void * __cdecl opaqueSeparatorColor() = 0 ;
	virtual void * __cdecl orangeColor() = 0 ;
	virtual void * __cdecl placeholderTextColor() = 0 ;
	virtual void * __cdecl purpleColor() = 0 ;
	virtual void * __cdecl quaternaryLabelColor() = 0 ;
	virtual void * __cdecl quaternarySystemFillColor() = 0 ;
	virtual void * __cdecl redColor() = 0 ;
	virtual void * __cdecl scrollViewTexturedBackgroundColor() = 0 ;
	virtual void * __cdecl secondaryLabelColor() = 0 ;
	virtual void * __cdecl secondarySystemBackgroundColor() = 0 ;
	virtual void * __cdecl secondarySystemFillColor() = 0 ;
	virtual void * __cdecl secondarySystemGroupedBackgroundColor() = 0 ;
	virtual void * __cdecl separatorColor() = 0 ;
	virtual void * __cdecl systemBackgroundColor() = 0 ;
	virtual void * __cdecl systemBlueColor() = 0 ;
	virtual void * __cdecl systemFillColor() = 0 ;
	virtual void * __cdecl systemGray2Color() = 0 ;
	virtual void * __cdecl systemGray3Color() = 0 ;
	virtual void * __cdecl systemGray4Color() = 0 ;
	virtual void * __cdecl systemGray5Color() = 0 ;
	virtual void * __cdecl systemGray6Color() = 0 ;
	virtual void * __cdecl systemGrayColor() = 0 ;
	virtual void * __cdecl systemGreenColor() = 0 ;
	virtual void * __cdecl systemGroupedBackgroundColor() = 0 ;
	virtual void * __cdecl systemIndigoColor() = 0 ;
	virtual void * __cdecl systemOrangeColor() = 0 ;
	virtual void * __cdecl systemPinkColor() = 0 ;
	virtual void * __cdecl systemPurpleColor() = 0 ;
	virtual void * __cdecl systemRedColor() = 0 ;
	virtual void * __cdecl systemTealColor() = 0 ;
	virtual void * __cdecl systemYellowColor() = 0 ;
	virtual void * __cdecl tertiaryLabelColor() = 0 ;
	virtual void * __cdecl tertiarySystemBackgroundColor() = 0 ;
	virtual void * __cdecl tertiarySystemFillColor() = 0 ;
	virtual void * __cdecl tertiarySystemGroupedBackgroundColor() = 0 ;
	virtual void * __cdecl underPageBackgroundColor() = 0 ;
	virtual void * __cdecl viewFlipsideBackgroundColor() = 0 ;
	virtual void * __cdecl whiteColor() = 0 ;
	virtual void * __cdecl yellowColor() = 0 ;
};

__interface  INTERFACE_UUID("{34723B19-45A7-43C6-9587-D091CF58F602}") UIColor  : public Iosapi::Foundation::NSObject 
{
	virtual void * __cdecl CGColor() = 0 ;
	virtual Iosapi::Coreimage::_di_CIColor __cdecl CIColor() = 0 ;
	virtual _di_UIColor __cdecl colorWithAlphaComponent(double alpha) = 0 ;
	virtual bool __cdecl getHue(Iosapi::Cocoatypes::PCGFloat hue, Iosapi::Cocoatypes::PCGFloat saturation, Iosapi::Cocoatypes::PCGFloat brightness, Iosapi::Cocoatypes::PCGFloat alpha) = 0 ;
	virtual bool __cdecl getRed(Iosapi::Cocoatypes::PCGFloat red, Iosapi::Cocoatypes::PCGFloat green, Iosapi::Cocoatypes::PCGFloat blue, Iosapi::Cocoatypes::PCGFloat alpha) = 0 ;
	virtual bool __cdecl getWhite(Iosapi::Cocoatypes::PCGFloat white, Iosapi::Cocoatypes::PCGFloat alpha) = 0 ;
	virtual _di_UIColor __cdecl initWithCGColor(void * cgColor) = 0 ;
	virtual _di_UIColor __cdecl initWithCIColor(Iosapi::Coreimage::_di_CIColor ciColor) = 0 ;
	virtual _di_UIColor __cdecl initWithHue(double hue, double saturation, double brightness, double alpha) = 0 ;
	virtual _di_UIColor __cdecl initWithPatternImage(_di_UIImage image) = 0 ;
	virtual _di_UIColor __cdecl initWithRed(double red, double green, double blue, double alpha) = 0 ;
	virtual _di_UIColor __cdecl initWithWhite(double white, double alpha) = 0 ;
	virtual void __cdecl setFill() = 0 ;
	virtual void __cdecl setStroke() = 0 ;
};

class PASCALIMPLEMENTATION TUIColor : public Macapi::Objectivec::TOCGenericImport__2<_di_UIColorClass,_di_UIColor>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UIColorClass,_di_UIColor> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUIColor(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UIColorClass,_di_UIColor>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUIColor() { }
	
};


__interface  INTERFACE_UUID("{01229171-8B2E-4A8C-B3B3-BDF2B4F318A0}") UITabBarItemClass  : public UIBarItemClass 
{
	
};

__interface  INTERFACE_UUID("{3F568C31-B6AC-4A32-964A-45E1115CD86E}") UITabBarItem  : public UIBarItem 
{
	virtual Iosapi::Foundation::_di_NSString __cdecl badgeValue() = 0 ;
	virtual _di_UIImage __cdecl finishedSelectedImage() = 0 ;
	virtual _di_UIImage __cdecl finishedUnselectedImage() = 0 ;
	virtual void * __cdecl initWithTabBarSystemItem(long systemItem, long tag) = 0 ;
	virtual void * __cdecl initWithTitle(Iosapi::Foundation::_di_NSString title, _di_UIImage image, long tag) = 0 ;
	virtual void __cdecl setBadgeValue(Iosapi::Foundation::_di_NSString badgeValue) = 0 ;
	virtual void __cdecl setFinishedSelectedImage(_di_UIImage selectedImage, _di_UIImage withFinishedUnselectedImage) = 0 ;
	virtual void __cdecl setTitlePositionAdjustment(UIOffset adjustment) = 0 ;
	virtual UIOffset __cdecl titlePositionAdjustment() = 0 ;
};

class PASCALIMPLEMENTATION TUITabBarItem : public Macapi::Objectivec::TOCGenericImport__2<_di_UITabBarItemClass,_di_UITabBarItem>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UITabBarItemClass,_di_UITabBarItem> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUITabBarItem(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UITabBarItemClass,_di_UITabBarItem>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUITabBarItem() { }
	
};


__interface  INTERFACE_UUID("{7BA89951-9958-438A-96FD-31AE70FDDC69}") UIRotationGestureRecognizerClass  : public UIGestureRecognizerClass 
{
	
};

__interface  INTERFACE_UUID("{7F1A0138-65D3-4D00-BDD0-193A7F68123C}") UIRotationGestureRecognizer  : public UIGestureRecognizer 
{
	virtual double __cdecl rotation() = 0 ;
	virtual void __cdecl setRotation(double rotation) = 0 ;
	virtual double __cdecl velocity() = 0 ;
};

class PASCALIMPLEMENTATION TUIRotationGestureRecognizer : public Macapi::Objectivec::TOCGenericImport__2<_di_UIRotationGestureRecognizerClass,_di_UIRotationGestureRecognizer>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UIRotationGestureRecognizerClass,_di_UIRotationGestureRecognizer> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUIRotationGestureRecognizer(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UIRotationGestureRecognizerClass,_di_UIRotationGestureRecognizer>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUIRotationGestureRecognizer() { }
	
};


__interface  INTERFACE_UUID("{CB16C222-B625-48D9-8710-3EE9789C06E0}") UISwipeGestureRecognizerClass  : public UIGestureRecognizerClass 
{
	
};

__interface  INTERFACE_UUID("{6ABB9B3E-CEB2-40A0-BCDD-EBA3BDE457CB}") UISwipeGestureRecognizer  : public UIGestureRecognizer 
{
	virtual unsigned long __cdecl direction() = 0 ;
	virtual unsigned long __cdecl numberOfTouchesRequired() = 0 ;
	virtual void __cdecl setDirection(unsigned long direction) = 0 ;
	virtual void __cdecl setNumberOfTouchesRequired(unsigned long numberOfTouchesRequired) = 0 ;
};

class PASCALIMPLEMENTATION TUISwipeGestureRecognizer : public Macapi::Objectivec::TOCGenericImport__2<_di_UISwipeGestureRecognizerClass,_di_UISwipeGestureRecognizer>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UISwipeGestureRecognizerClass,_di_UISwipeGestureRecognizer> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUISwipeGestureRecognizer(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UISwipeGestureRecognizerClass,_di_UISwipeGestureRecognizer>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUISwipeGestureRecognizer() { }
	
};


__interface  INTERFACE_UUID("{24405DD9-36FB-4E69-A18C-ED2C0BBBEBE9}") UIPinchGestureRecognizerClass  : public UIGestureRecognizerClass 
{
	
};

__interface  INTERFACE_UUID("{54C67364-172A-48EC-8BF4-976954CB7815}") UIPinchGestureRecognizer  : public UIGestureRecognizer 
{
	virtual double __cdecl scale() = 0 ;
	virtual void __cdecl setScale(double scale) = 0 ;
	virtual double __cdecl velocity() = 0 ;
};

class PASCALIMPLEMENTATION TUIPinchGestureRecognizer : public Macapi::Objectivec::TOCGenericImport__2<_di_UIPinchGestureRecognizerClass,_di_UIPinchGestureRecognizer>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UIPinchGestureRecognizerClass,_di_UIPinchGestureRecognizer> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUIPinchGestureRecognizer(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UIPinchGestureRecognizerClass,_di_UIPinchGestureRecognizer>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUIPinchGestureRecognizer() { }
	
};


__interface  INTERFACE_UUID("{CC233A69-E4E8-4D9D-BA7E-70B778B9C0DE}") UIMarkupTextPrintFormatterClass  : public UIPrintFormatterClass 
{
	
};

__interface  INTERFACE_UUID("{DD819284-024F-4002-90CF-649F63E9A5D5}") UIMarkupTextPrintFormatter  : public UIPrintFormatter 
{
	virtual void * __cdecl initWithMarkupText(Iosapi::Foundation::_di_NSString markupText) = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl markupText() = 0 ;
	virtual void __cdecl setMarkupText(Iosapi::Foundation::_di_NSString markupText) = 0 ;
};

class PASCALIMPLEMENTATION TUIMarkupTextPrintFormatter : public Macapi::Objectivec::TOCGenericImport__2<_di_UIMarkupTextPrintFormatterClass,_di_UIMarkupTextPrintFormatter>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UIMarkupTextPrintFormatterClass,_di_UIMarkupTextPrintFormatter> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUIMarkupTextPrintFormatter(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UIMarkupTextPrintFormatterClass,_di_UIMarkupTextPrintFormatter>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUIMarkupTextPrintFormatter() { }
	
};


typedef void __fastcall (__closure *TOnUIViewControllerCompletion)(void);

__interface  INTERFACE_UUID("{87E0A407-94C1-4DC4-AA14-FB3C3BC619D1}") UIViewControllerClass  : public UIResponderClass 
{
	virtual void __cdecl attemptRotationToDeviceOrientation() = 0 ;
};

__interface  INTERFACE_UUID("{F7A5E372-3F4A-4F25-A2F9-C91D7CB5FC09}") UIViewController  : public UIResponder 
{
	virtual void __cdecl addChildViewController(_di_UIViewController childController) = 0 ;
	virtual bool __cdecl automaticallyForwardAppearanceAndRotationMethodsToChildViewControllers() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl childViewControllers() = 0 ;
	virtual Iosapi::Foundation::NSSize __cdecl contentSizeForViewInPopover() = 0 ;
	virtual bool __cdecl definesPresentationContext() = 0 ;
	virtual void __cdecl didAnimateFirstHalfOfRotationToInterfaceOrientation(long toInterfaceOrientation) = 0 ;
	virtual void __cdecl didMoveToParentViewController(_di_UIViewController parent) = 0 ;
	virtual void __cdecl didReceiveMemoryWarning() = 0 ;
	virtual void __cdecl didRotateFromInterfaceOrientation(long fromInterfaceOrientation) = 0 ;
	virtual bool __cdecl disablesAutomaticKeyboardDismissal() = 0 ;
	virtual void __cdecl dismissModalViewControllerAnimated(bool animated) = 0 ;
	virtual _di_UIBarButtonItem __cdecl editButtonItem() = 0 ;
	virtual bool __cdecl hidesBottomBarWhenPushed() = 0 ;
	virtual void * __cdecl initWithNibName(Iosapi::Foundation::_di_NSString nibNameOrNil, Iosapi::Foundation::_di_NSBundle bundle) = 0 ;
	virtual long __cdecl interfaceOrientation() = 0 ;
	virtual bool __cdecl isBeingDismissed() = 0 ;
	virtual bool __cdecl isBeingPresented() = 0 ;
	virtual bool __cdecl isEditing() = 0 ;
	virtual bool __cdecl isModalInPopover() = 0 ;
	virtual bool __cdecl isMovingFromParentViewController() = 0 ;
	virtual bool __cdecl isMovingToParentViewController() = 0 ;
	virtual bool __cdecl isViewLoaded() = 0 ;
	virtual void __cdecl loadView() = 0 ;
	virtual long __cdecl modalPresentationStyle() = 0 ;
	virtual long __cdecl modalTransitionStyle() = 0 ;
	virtual _di_UIViewController __cdecl modalViewController() = 0 ;
	virtual _di_UINavigationController __cdecl navigationController() = 0 ;
	virtual _di_UINavigationItem __cdecl navigationItem() = 0 ;
	virtual Iosapi::Foundation::_di_NSBundle __cdecl nibBundle() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl nibName() = 0 ;
	virtual _di_UIViewController __cdecl parentViewController() = 0 ;
	virtual void __cdecl performSegueWithIdentifier(Iosapi::Foundation::_di_NSString identifier, void * sender) = 0 ;
	virtual void __cdecl prepareForSegue(_di_UIStoryboardSegue segue, void * sender) = 0 ;
	virtual void __cdecl presentModalViewController(_di_UIViewController modalViewController, bool animated) = 0 ;
	virtual void __cdecl presentViewController(_di_UIViewController viewControllerToPresent, bool animated, TOnUIViewControllerCompletion completion) = 0 ;
	virtual void __cdecl dismissViewControllerAnimated(bool flag, TOnUIViewControllerCompletion completion) = 0 ;
	virtual _di_UIViewController __cdecl presentedViewController() = 0 ;
	virtual _di_UIViewController __cdecl presentingViewController() = 0 ;
	virtual bool __cdecl providesPresentationContextTransitionStyle() = 0 ;
	virtual void __cdecl removeFromParentViewController() = 0 ;
	virtual _di_UIView __cdecl rotatingFooterView() = 0 ;
	virtual _di_UIView __cdecl rotatingHeaderView() = 0 ;
	virtual _di_UISearchDisplayController __cdecl searchDisplayController() = 0 ;
	virtual void __cdecl setContentSizeForViewInPopover(Iosapi::Foundation::NSSize contentSizeForViewInPopover) = 0 ;
	virtual void __cdecl setDefinesPresentationContext(bool definesPresentationContext) = 0 ;
	virtual void __cdecl setEditing(bool editing) = 0 /* overload */;
	virtual void __cdecl setEditing(bool editing, bool animated) = 0 /* overload */;
	virtual void __cdecl setHidesBottomBarWhenPushed(bool hidesBottomBarWhenPushed) = 0 ;
	virtual void __cdecl setModalInPopover(bool modalInPopover) = 0 ;
	virtual void __cdecl setModalPresentationStyle(long modalPresentationStyle) = 0 ;
	virtual void __cdecl setModalTransitionStyle(long modalTransitionStyle) = 0 ;
	virtual void __cdecl setProvidesPresentationContextTransitionStyle(bool providesPresentationContextTransitionStyle) = 0 ;
	virtual void __cdecl setNeedsStatusBarAppearanceUpdate() = 0 ;
	virtual void __cdecl setTabBarItem(_di_UITabBarItem tabBarItem) = 0 ;
	virtual void __cdecl setTitle(Iosapi::Foundation::_di_NSString title) = 0 ;
	virtual void __cdecl setToolbarItems(Iosapi::Foundation::_di_NSArray toolbarItems) = 0 /* overload */;
	virtual void __cdecl setToolbarItems(Iosapi::Foundation::_di_NSArray toolbarItems, bool animated) = 0 /* overload */;
	virtual void __cdecl setView(_di_UIView view) = 0 ;
	virtual void __cdecl setWantsFullScreenLayout(bool wantsFullScreenLayout) = 0 ;
	virtual bool __cdecl shouldAutorotateToInterfaceOrientation(long toInterfaceOrientation) = 0 ;
	virtual _di_UISplitViewController __cdecl splitViewController() = 0 ;
	virtual _di_UIStoryboard __cdecl storyboard() = 0 ;
	virtual _di_UITabBarController __cdecl tabBarController() = 0 ;
	virtual _di_UITabBarItem __cdecl tabBarItem() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl title() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl toolbarItems() = 0 ;
	virtual _di_UIView __cdecl view() = 0 ;
	virtual void __cdecl viewDidAppear(bool animated) = 0 ;
	virtual void __cdecl viewDidDisappear(bool animated) = 0 ;
	virtual void __cdecl viewDidLayoutSubviews() = 0 ;
	virtual void __cdecl viewDidLoad() = 0 ;
	virtual void __cdecl viewDidUnload() = 0 ;
	virtual void __cdecl viewWillAppear(bool animated) = 0 ;
	virtual void __cdecl viewWillDisappear(bool animated) = 0 ;
	virtual void __cdecl viewWillLayoutSubviews() = 0 ;
	virtual void __cdecl viewWillUnload() = 0 ;
	virtual bool __cdecl wantsFullScreenLayout() = 0 ;
	virtual void __cdecl willAnimateFirstHalfOfRotationToInterfaceOrientation(long toInterfaceOrientation, double duration) = 0 ;
	virtual void __cdecl willAnimateRotationToInterfaceOrientation(long toInterfaceOrientation, double duration) = 0 ;
	virtual void __cdecl willAnimateSecondHalfOfRotationFromInterfaceOrientation(long fromInterfaceOrientation, double duration) = 0 ;
	virtual void __cdecl willMoveToParentViewController(_di_UIViewController parent) = 0 ;
	virtual void __cdecl willRotateToInterfaceOrientation(long toInterfaceOrientation, double duration) = 0 ;
	virtual bool __cdecl shouldPerformSegueWithIdentifier(Iosapi::Foundation::_di_NSString identifier, void * sender) = 0 ;
	virtual bool __cdecl canPerformUnwindSegueAction(void * action, _di_UIViewController fromViewController, void * withSender) = 0 ;
	virtual _di_UIViewController __cdecl viewControllerForUnwindSegueAction(void * action, _di_UIViewController fromViewController, void * withSender) = 0 ;
	virtual _di_UIStoryboardSegue __cdecl segueForUnwindingToViewController(_di_UIViewController toViewController, _di_UIViewController fromViewController, Iosapi::Foundation::_di_NSString identifier) = 0 ;
	virtual void __cdecl setModalPresentationCapturesStatusBarAppearance(bool modalPresentationCapturesStatusBarAppearance) = 0 ;
	virtual bool __cdecl modalPresentationCapturesStatusBarAppearance() = 0 ;
	virtual void __cdecl setEdgesForExtendedLayout(unsigned long edgesForExtendedLayout) = 0 ;
	virtual unsigned long __cdecl edgesForExtendedLayout() = 0 ;
	virtual void __cdecl setExtendedLayoutIncludesOpaqueBars(bool extendedLayoutIncludesOpaqueBars) = 0 ;
	virtual bool __cdecl extendedLayoutIncludesOpaqueBars() = 0 ;
	virtual void __cdecl setAutomaticallyAdjustsScrollViewInsets(bool automaticallyAdjustsScrollViewInsets) = 0 ;
	virtual bool __cdecl automaticallyAdjustsScrollViewInsets() = 0 ;
	virtual void __cdecl setPreferredContentSize(Iosapi::Foundation::NSSize preferredContentSize) = 0 ;
	virtual Iosapi::Foundation::NSSize __cdecl preferredContentSize() = 0 ;
	virtual long __cdecl preferredStatusBarStyle() = 0 ;
	virtual bool __cdecl prefersStatusBarHidden() = 0 ;
	virtual long __cdecl preferredStatusBarUpdateAnimation() = 0 ;
	virtual _di_UIViewController __cdecl targetViewControllerForAction(void * action, void * sender) = 0 ;
	virtual void __cdecl showViewController(_di_UIViewController vc, void * sender) = 0 ;
	virtual void __cdecl showDetailViewController(_di_UIViewController vc, void * sender) = 0 ;
	virtual bool __cdecl shouldAutorotate() = 0 ;
	virtual unsigned long __cdecl supportedInterfaceOrientations() = 0 ;
	virtual long __cdecl preferredInterfaceOrientationForPresentation() = 0 ;
	virtual void __cdecl transitionFromViewController(_di_UIViewController fromViewController, _di_UIViewController toViewController, double duration, unsigned long options, TUIKitAction animations, TUIKitCompletion completion) = 0 ;
	virtual void __cdecl beginAppearanceTransition(bool isAppearing, bool animated) = 0 ;
	virtual void __cdecl endAppearanceTransition() = 0 ;
	virtual _di_UIViewController __cdecl childViewControllerForStatusBarStyle() = 0 ;
	virtual _di_UIViewController __cdecl childViewControllerForStatusBarHidden() = 0 ;
	virtual void __cdecl setOverrideTraitCollection(_di_UITraitCollection collection, _di_UIViewController forChildViewController) = 0 ;
	virtual _di_UITraitCollection __cdecl overrideTraitCollectionForChildViewController(_di_UIViewController childViewController) = 0 ;
	virtual bool __cdecl shouldAutomaticallyForwardRotationMethods() = 0 ;
	virtual bool __cdecl shouldAutomaticallyForwardAppearanceMethods() = 0 ;
	virtual void __cdecl setRestorationIdentifier(Iosapi::Foundation::_di_NSString restorationIdentifier) = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl restorationIdentifier() = 0 ;
	virtual void __cdecl setRestorationClass(void * restorationClass) = 0 ;
	virtual void * __cdecl restorationClass() = 0 ;
	virtual void __cdecl encodeRestorableStateWithCoder(Iosapi::Foundation::_di_NSCoder coder) = 0 ;
	virtual void __cdecl decodeRestorableStateWithCoder(Iosapi::Foundation::_di_NSCoder coder) = 0 ;
	virtual void __cdecl applicationFinishedRestoringState() = 0 ;
	virtual void __cdecl updateViewConstraints() = 0 ;
	virtual void __cdecl setTransitioningDelegate(void * transitioningDelegate) = 0 ;
	virtual void * __cdecl transitioningDelegate() = 0 ;
	virtual void * __cdecl topLayoutGuide() = 0 ;
	virtual void * __cdecl bottomLayoutGuide() = 0 ;
	virtual Iosapi::Foundation::_di_NSExtensionContext __cdecl extensionContext() = 0 ;
	virtual _di_UIPresentationController __cdecl presentationController() = 0 ;
	virtual _di_UIPopoverPresentationController __cdecl popoverPresentationController() = 0 ;
	virtual void * __cdecl transitionCoordinator() = 0 ;
	virtual void __cdecl collapseSecondaryViewController(_di_UIViewController secondaryViewController, _di_UISplitViewController forSplitViewController) = 0 ;
	virtual _di_UIViewController __cdecl separateSecondaryViewControllerForSplitViewController(_di_UISplitViewController splitViewController) = 0 ;
	virtual void __cdecl preferredContentSizeDidChangeForChildContentContainer(void * container) = 0 ;
	virtual void __cdecl systemLayoutFittingSizeDidChangeForChildContentContainer(void * container) = 0 ;
	virtual Iosapi::Foundation::NSSize __cdecl sizeForChildContentContainer(void * container, Iosapi::Foundation::NSSize withParentContainerSize) = 0 ;
	virtual void __cdecl viewWillTransitionToSize(Iosapi::Foundation::NSSize size, _di_UIViewControllerTransitionCoordinator withTransitionCoordinator) = 0 ;
	virtual void __cdecl willTransitionToTraitCollection(_di_UITraitCollection newCollection, void * withTransitionCoordinator) = 0 ;
};

class PASCALIMPLEMENTATION TUIViewController : public Macapi::Objectivec::TOCGenericImport__2<_di_UIViewControllerClass,_di_UIViewController>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UIViewControllerClass,_di_UIViewController> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUIViewController(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UIViewControllerClass,_di_UIViewController>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUIViewController() { }
	
};


__interface  INTERFACE_UUID("{287CC128-E9B5-4B76-A63F-9D6632EF6950}") UIBarButtonItemClass  : public UIBarItemClass 
{
	
};

__interface  INTERFACE_UUID("{3C056056-41D4-44E8-A3B1-D16DA7666333}") UIBarButtonItem  : public UIBarItem 
{
	virtual void * __cdecl action() = 0 ;
	virtual _di_UIImage __cdecl backButtonBackgroundImageForState(unsigned long state, long barMetrics) = 0 ;
	virtual double __cdecl backButtonBackgroundVerticalPositionAdjustmentForBarMetrics(long barMetrics) = 0 ;
	virtual UIOffset __cdecl backButtonTitlePositionAdjustmentForBarMetrics(long barMetrics) = 0 ;
	virtual _di_UIImage __cdecl backgroundImageForState(unsigned long state, long barMetrics) = 0 ;
	virtual double __cdecl backgroundVerticalPositionAdjustmentForBarMetrics(long barMetrics) = 0 ;
	virtual _di_UIView __cdecl customView() = 0 ;
	virtual void * __cdecl initWithBarButtonSystemItem(long systemItem, void * target, void * action) = 0 ;
	virtual void * __cdecl initWithCustomView(_di_UIView customView) = 0 ;
	virtual void * __cdecl initWithImage(_di_UIImage image, _di_UIImage landscapeImagePhone, long style, void * target, void * action) = 0 /* overload */;
	virtual void * __cdecl initWithImage(_di_UIImage image, long style, void * target, void * action) = 0 /* overload */;
	virtual void * __cdecl initWithTitle(Iosapi::Foundation::_di_NSString title, long style, void * target, void * action) = 0 ;
	virtual Iosapi::Foundation::_di_NSSet __cdecl possibleTitles() = 0 ;
	virtual void __cdecl setAction(void * action) = 0 ;
	virtual void __cdecl setBackButtonBackgroundImage(_di_UIImage backgroundImage, unsigned long forState, long barMetrics) = 0 ;
	virtual void __cdecl setBackButtonBackgroundVerticalPositionAdjustment(double adjustment, long forBarMetrics) = 0 ;
	virtual void __cdecl setBackButtonTitlePositionAdjustment(UIOffset adjustment, long forBarMetrics) = 0 ;
	virtual void __cdecl setBackgroundImage(_di_UIImage backgroundImage, unsigned long forState, long barMetrics) = 0 ;
	virtual void __cdecl setBackgroundVerticalPositionAdjustment(double adjustment, long forBarMetrics) = 0 ;
	virtual void __cdecl setCustomView(_di_UIView customView) = 0 ;
	virtual void __cdecl setPossibleTitles(Iosapi::Foundation::_di_NSSet possibleTitles) = 0 ;
	virtual void __cdecl setStyle(long style) = 0 ;
	virtual void __cdecl setTarget(void * target) = 0 ;
	virtual void __cdecl setTintColor(_di_UIColor tintColor) = 0 ;
	virtual void __cdecl setTitlePositionAdjustment(UIOffset adjustment, long forBarMetrics) = 0 ;
	virtual void __cdecl setWidth(double width) = 0 ;
	virtual long __cdecl style() = 0 ;
	virtual void * __cdecl target() = 0 ;
	virtual _di_UIColor __cdecl tintColor() = 0 ;
	virtual UIOffset __cdecl titlePositionAdjustmentForBarMetrics(long barMetrics) = 0 ;
	virtual double __cdecl width() = 0 ;
};

class PASCALIMPLEMENTATION TUIBarButtonItem : public Macapi::Objectivec::TOCGenericImport__2<_di_UIBarButtonItemClass,_di_UIBarButtonItem>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UIBarButtonItemClass,_di_UIBarButtonItem> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUIBarButtonItem(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UIBarButtonItemClass,_di_UIBarButtonItem>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUIBarButtonItem() { }
	
};


__interface  INTERFACE_UUID("{30C71FB1-FDCB-4BA7-A838-84E65721AA6F}") UILongPressGestureRecognizerClass  : public UIGestureRecognizerClass 
{
	
};

__interface  INTERFACE_UUID("{9A7D268A-9CE3-4FB7-9593-A1A3E9D26C58}") UILongPressGestureRecognizer  : public UIGestureRecognizer 
{
	virtual double __cdecl allowableMovement() = 0 ;
	virtual double __cdecl minimumPressDuration() = 0 ;
	virtual long __cdecl numberOfTapsRequired() = 0 ;
	virtual long __cdecl numberOfTouchesRequired() = 0 ;
	virtual void __cdecl setAllowableMovement(double allowableMovement) = 0 ;
	virtual void __cdecl setMinimumPressDuration(double minimumPressDuration) = 0 ;
	virtual void __cdecl setNumberOfTapsRequired(long numberOfTapsRequired) = 0 ;
	virtual void __cdecl setNumberOfTouchesRequired(long numberOfTouchesRequired) = 0 ;
};

class PASCALIMPLEMENTATION TUILongPressGestureRecognizer : public Macapi::Objectivec::TOCGenericImport__2<_di_UILongPressGestureRecognizerClass,_di_UILongPressGestureRecognizer>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UILongPressGestureRecognizerClass,_di_UILongPressGestureRecognizer> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUILongPressGestureRecognizer(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UILongPressGestureRecognizerClass,_di_UILongPressGestureRecognizer>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUILongPressGestureRecognizer() { }
	
};


__interface  INTERFACE_UUID("{1711C743-A68F-4EC3-B47C-6C92F317095F}") UIManagedDocumentClass  : public UIDocumentClass 
{
	virtual Iosapi::Foundation::_di_NSString __cdecl persistentStoreName() = 0 ;
};

__interface  INTERFACE_UUID("{CB729C37-3C01-48CB-8CA8-50FFEB780ABB}") UIManagedDocument  : public UIDocument 
{
	virtual void * __cdecl additionalContentForURL(Iosapi::Foundation::_di_NSURL absoluteURL, Iosapi::Foundation::_di_NSError error) = 0 ;
	virtual bool __cdecl configurePersistentStoreCoordinatorForURL(Iosapi::Foundation::_di_NSURL storeURL, Iosapi::Foundation::_di_NSString ofType, Iosapi::Foundation::_di_NSString modelConfiguration, Iosapi::Foundation::_di_NSDictionary storeOptions, Iosapi::Foundation::_di_NSError error) = 0 ;
	virtual Iosapi::Coredata::_di_NSManagedObjectContext __cdecl managedObjectContext() = 0 ;
	virtual Iosapi::Coredata::_di_NSManagedObjectModel __cdecl managedObjectModel() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl modelConfiguration() = 0 ;
	virtual Iosapi::Foundation::_di_NSDictionary __cdecl persistentStoreOptions() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl persistentStoreTypeForFileType(Iosapi::Foundation::_di_NSString fileType) = 0 ;
	virtual bool __cdecl readAdditionalContentFromURL(Iosapi::Foundation::_di_NSURL absoluteURL, Iosapi::Foundation::_di_NSError error) = 0 ;
	virtual void __cdecl setModelConfiguration(Iosapi::Foundation::_di_NSString modelConfiguration) = 0 ;
	virtual void __cdecl setPersistentStoreOptions(Iosapi::Foundation::_di_NSDictionary persistentStoreOptions) = 0 ;
	virtual bool __cdecl writeAdditionalContent(void * content, Iosapi::Foundation::_di_NSURL toURL, Iosapi::Foundation::_di_NSURL originalContentsURL, Iosapi::Foundation::_di_NSError error) = 0 ;
};

class PASCALIMPLEMENTATION TUIManagedDocument : public Macapi::Objectivec::TOCGenericImport__2<_di_UIManagedDocumentClass,_di_UIManagedDocument>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UIManagedDocumentClass,_di_UIManagedDocument> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUIManagedDocument(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UIManagedDocumentClass,_di_UIManagedDocument>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUIManagedDocument() { }
	
};


__interface  INTERFACE_UUID("{23C73E69-9AF1-4080-93DA-E405E08B6FDD}") UISimpleTextPrintFormatterClass  : public UIPrintFormatterClass 
{
	
};

__interface  INTERFACE_UUID("{C0D1AFC9-347B-400B-B1F2-8F2420C4B41C}") UISimpleTextPrintFormatter  : public UIPrintFormatter 
{
	virtual _di_UIColor __cdecl color() = 0 ;
	virtual _di_UIFont __cdecl font() = 0 ;
	virtual void * __cdecl initWithText(Iosapi::Foundation::_di_NSString text) = 0 ;
	virtual void __cdecl setColor(_di_UIColor color) = 0 ;
	virtual void __cdecl setFont(_di_UIFont font) = 0 ;
	virtual void __cdecl setText(Iosapi::Foundation::_di_NSString text) = 0 ;
	virtual void __cdecl setTextAlignment(long textAlignment) = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl text() = 0 ;
	virtual long __cdecl textAlignment() = 0 ;
};

class PASCALIMPLEMENTATION TUISimpleTextPrintFormatter : public Macapi::Objectivec::TOCGenericImport__2<_di_UISimpleTextPrintFormatterClass,_di_UISimpleTextPrintFormatter>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UISimpleTextPrintFormatterClass,_di_UISimpleTextPrintFormatter> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUISimpleTextPrintFormatter(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UISimpleTextPrintFormatterClass,_di_UISimpleTextPrintFormatter>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUISimpleTextPrintFormatter() { }
	
};


__interface  INTERFACE_UUID("{04F97651-346C-4F06-A92E-15FC47E9FB1A}") UIPanGestureRecognizerClass  : public UIGestureRecognizerClass 
{
	
};

__interface  INTERFACE_UUID("{AE52DAD1-5A76-41DF-8043-6A54236B4459}") UIPanGestureRecognizer  : public UIGestureRecognizer 
{
	virtual unsigned long __cdecl maximumNumberOfTouches() = 0 ;
	virtual unsigned long __cdecl minimumNumberOfTouches() = 0 ;
	virtual void __cdecl setMaximumNumberOfTouches(unsigned long maximumNumberOfTouches) = 0 ;
	virtual void __cdecl setMinimumNumberOfTouches(unsigned long minimumNumberOfTouches) = 0 ;
	virtual void __cdecl setTranslation(Iosapi::Foundation::NSPoint translation, _di_UIView inView) = 0 ;
	virtual Iosapi::Foundation::NSPoint __cdecl translationInView(_di_UIView view) = 0 ;
	virtual Iosapi::Foundation::NSPoint __cdecl velocityInView(_di_UIView view) = 0 ;
};

class PASCALIMPLEMENTATION TUIPanGestureRecognizer : public Macapi::Objectivec::TOCGenericImport__2<_di_UIPanGestureRecognizerClass,_di_UIPanGestureRecognizer>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UIPanGestureRecognizerClass,_di_UIPanGestureRecognizer> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUIPanGestureRecognizer(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UIPanGestureRecognizerClass,_di_UIPanGestureRecognizer>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUIPanGestureRecognizer() { }
	
};


__interface  INTERFACE_UUID("{E2E1985B-A9CC-4313-A4DA-40365CAA63E8}") UIStoryboardPopoverSegueClass  : public UIStoryboardSegueClass 
{
	
};

__interface  INTERFACE_UUID("{D20BB5C9-6212-47B3-9ABF-2C8FEA565230}") UIStoryboardPopoverSegue  : public UIStoryboardSegue 
{
	virtual _di_UIPopoverController __cdecl popoverController() = 0 ;
};

class PASCALIMPLEMENTATION TUIStoryboardPopoverSegue : public Macapi::Objectivec::TOCGenericImport__2<_di_UIStoryboardPopoverSegueClass,_di_UIStoryboardPopoverSegue>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UIStoryboardPopoverSegueClass,_di_UIStoryboardPopoverSegue> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUIStoryboardPopoverSegue(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UIStoryboardPopoverSegueClass,_di_UIStoryboardPopoverSegue>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUIStoryboardPopoverSegue() { }
	
};


typedef void __fastcall (__closure *TUIApplicationBackgroundTaskCompletionHandler)(void);

typedef void __fastcall (__closure *TUIApplicationAlternateIconNameCompletionHandler)(Iosapi::Foundation::_di_NSError error);

__interface  INTERFACE_UUID("{EB8D5CD5-75CA-469F-B1B9-3A32D640B450}") UIApplicationClass  : public UIResponderClass 
{
	virtual void * __cdecl sharedApplication() = 0 ;
};

__interface  INTERFACE_UUID("{BD1002BE-B8C1-45BE-9AB8-9720A9EB1102}") UIApplication  : public UIResponder 
{
	virtual Iosapi::Foundation::_di_NSString __cdecl alternateIconName() = 0 ;
	virtual long __cdecl applicationIconBadgeNumber() = 0 ;
	virtual long __cdecl applicationState() = 0 ;
	virtual bool __cdecl applicationSupportsShakeToEdit() = 0 ;
	virtual long __cdecl backgroundRefreshStatus() = 0 ;
	virtual double __cdecl backgroundTimeRemaining() = 0 ;
	virtual unsigned long __cdecl beginBackgroundTaskWithExpirationHandler(TUIApplicationBackgroundTaskCompletionHandler handler) = 0 ;
	virtual unsigned long __cdecl beginBackgroundTaskWithName(Iosapi::Foundation::_di_NSString taskName, TUIApplicationBackgroundTaskCompletionHandler handler) = 0 ;
	virtual void __cdecl beginIgnoringInteractionEvents() = 0 ;
	virtual void __cdecl beginReceivingRemoteControlEvents() = 0 ;
	virtual bool __cdecl canOpenURL(Iosapi::Foundation::_di_NSURL url) = 0 ;
	virtual void __cdecl cancelAllLocalNotifications() = 0 ;
	virtual void __cdecl cancelLocalNotification(_di_UILocalNotification notification) = 0 ;
	virtual void __cdecl clearKeepAliveTimeout() = 0 ;
	virtual void __cdecl completeStateRestoration() = 0 ;
	virtual _di_UIUserNotificationSettings __cdecl currentUserNotificationSettings() = 0 ;
	virtual _di_UIApplicationDelegate __cdecl delegate() = 0 ;
	virtual void * __cdecl enabledRemoteNotificationTypes() = 0 ;
	virtual void __cdecl endBackgroundTask(void * identifier) = 0 ;
	virtual void __cdecl endIgnoringInteractionEvents() = 0 ;
	virtual void __cdecl endReceivingRemoteControlEvents() = 0 ;
	virtual void __cdecl ignoreSnapshotOnNextApplicationLaunch() = 0 ;
	virtual bool __cdecl isIdleTimerDisabled() = 0 ;
	virtual bool __cdecl isIgnoringInteractionEvents() = 0 ;
	virtual bool __cdecl isNetworkActivityIndicatorVisible() = 0 ;
	virtual bool __cdecl isProtectedDataAvailable() = 0 ;
	virtual bool __cdecl isRegisteredForRemoteNotifications() = 0 ;
	virtual bool __cdecl isStatusBarHidden() = 0 ;
	virtual _di_UIWindow __cdecl keyWindow() = 0 ;
	virtual bool __cdecl openURL(Iosapi::Foundation::_di_NSURL url) = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl preferredContentSizeCategory() = 0 ;
	virtual void __cdecl presentLocalNotificationNow(_di_UILocalNotification notification) = 0 ;
	virtual void __cdecl registerForRemoteNotificationTypes(void * types) = 0 ;
	virtual void __cdecl registerForRemoteNotifications() = 0 ;
	virtual void __cdecl registerUserNotificationSettings(_di_UIUserNotificationSettings notificationSettings) = 0 ;
	virtual void __cdecl scheduleLocalNotification(_di_UILocalNotification notification) = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl scheduledLocalNotifications() = 0 ;
	virtual void __cdecl sendEvent(_di_UIEvent event) = 0 ;
	virtual void __cdecl setAlternateIconName(Iosapi::Foundation::_di_NSString alternateIconName, TUIApplicationAlternateIconNameCompletionHandler completionHandler) = 0 ;
	virtual void __cdecl setApplicationIconBadgeNumber(long applicationIconBadgeNumber) = 0 ;
	virtual void __cdecl setApplicationSupportsShakeToEdit(bool applicationSupportsShakeToEdit) = 0 ;
	virtual void __cdecl setDelegate(_di_UIApplicationDelegate delegate) = 0 ;
	virtual void __cdecl setIdleTimerDisabled(bool idleTimerDisabled) = 0 ;
	virtual void __cdecl setMinimumBackgroundFetchInterval(double minimumBackgroundFetchInterval) = 0 ;
	virtual void __cdecl setNetworkActivityIndicatorVisible(bool networkActivityIndicatorVisible) = 0 ;
	virtual void __cdecl setNewsstandIconImage(_di_UIImage image) = 0 ;
	virtual void __cdecl setScheduledLocalNotifications(Iosapi::Foundation::_di_NSArray scheduledLocalNotifications) = 0 ;
	virtual void __cdecl setShortcutItems(Iosapi::Foundation::_di_NSArray shortcutItems) = 0 ;
	virtual void __cdecl setStatusBarHidden(bool statusBarHidden) = 0 /* overload */;
	virtual void __cdecl setStatusBarHidden(bool hidden, long withAnimation) = 0 /* overload */;
	virtual void __cdecl setStatusBarOrientation(long statusBarOrientation) = 0 /* overload */;
	virtual void __cdecl setStatusBarOrientation(long interfaceOrientation, bool animated) = 0 /* overload */;
	virtual void __cdecl setStatusBarStyle(long statusBarStyle) = 0 /* overload */;
	virtual void __cdecl setStatusBarStyle(long statusBarStyle, bool animated) = 0 /* overload */;
	virtual Iosapi::Foundation::_di_NSArray __cdecl shortcutItems() = 0 ;
	virtual Iosapi::Foundation::NSRect __cdecl statusBarFrame() = 0 ;
	virtual long __cdecl statusBarOrientation() = 0 ;
	virtual double __cdecl statusBarOrientationAnimationDuration() = 0 ;
	virtual long __cdecl statusBarStyle() = 0 ;
	virtual bool __cdecl supportsAlternateIcons() = 0 ;
	virtual void __cdecl unregisterForRemoteNotifications() = 0 ;
	virtual long __cdecl userInterfaceLayoutDirection() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl windows() = 0 ;
};

class PASCALIMPLEMENTATION TUIApplication : public Macapi::Objectivec::TOCGenericImport__2<_di_UIApplicationClass,_di_UIApplication>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UIApplicationClass,_di_UIApplication> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUIApplication(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UIApplicationClass,_di_UIApplication>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUIApplication() { }
	
};


__interface  INTERFACE_UUID("{7D474AB7-6437-4258-9DA9-51BE7473D0AD}") UIViewPrintFormatterClass  : public UIPrintFormatterClass 
{
	
};

__interface  INTERFACE_UUID("{595E8B80-CC94-41BC-8B94-41BE7DF984A6}") UIViewPrintFormatter  : public UIPrintFormatter 
{
	virtual _di_UIView __cdecl view() = 0 ;
};

class PASCALIMPLEMENTATION TUIViewPrintFormatter : public Macapi::Objectivec::TOCGenericImport__2<_di_UIViewPrintFormatterClass,_di_UIViewPrintFormatter>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UIViewPrintFormatterClass,_di_UIViewPrintFormatter> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUIViewPrintFormatter(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UIViewPrintFormatterClass,_di_UIViewPrintFormatter>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUIViewPrintFormatter() { }
	
};


__interface  INTERFACE_UUID("{B998245A-B96F-4BF8-B8D7-0FFC35E31DCA}") UITapGestureRecognizerClass  : public UIGestureRecognizerClass 
{
	
};

__interface  INTERFACE_UUID("{00DE2AD5-8E72-4513-BAEC-FD6E95D0B7AD}") UITapGestureRecognizer  : public UIGestureRecognizer 
{
	virtual unsigned long __cdecl numberOfTapsRequired() = 0 ;
	virtual unsigned long __cdecl numberOfTouchesRequired() = 0 ;
	virtual void __cdecl setNumberOfTapsRequired(unsigned long numberOfTapsRequired) = 0 ;
	virtual void __cdecl setNumberOfTouchesRequired(unsigned long numberOfTouchesRequired) = 0 ;
};

class PASCALIMPLEMENTATION TUITapGestureRecognizer : public Macapi::Objectivec::TOCGenericImport__2<_di_UITapGestureRecognizerClass,_di_UITapGestureRecognizer>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UITapGestureRecognizerClass,_di_UITapGestureRecognizer> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUITapGestureRecognizer(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UITapGestureRecognizerClass,_di_UITapGestureRecognizer>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUITapGestureRecognizer() { }
	
};


__interface  INTERFACE_UUID("{7A6BE447-0282-4E37-9DC8-64BC2417A6E9}") UIWebViewClass  : public UIViewClass 
{
	
};

__interface  INTERFACE_UUID("{787E0C18-F4B5-4A96-850F-B47D9122C74E}") UIWebView  : public UIView 
{
	virtual bool __cdecl allowsInlineMediaPlayback() = 0 ;
	virtual bool __cdecl canGoBack() = 0 ;
	virtual bool __cdecl canGoForward() = 0 ;
	virtual unsigned long __cdecl dataDetectorTypes() = 0 ;
	virtual void * __cdecl delegate() = 0 ;
	virtual bool __cdecl detectsPhoneNumbers() = 0 ;
	virtual void __cdecl goBack() = 0 ;
	virtual void __cdecl goForward() = 0 ;
	virtual bool __cdecl isLoading() = 0 ;
	virtual void __cdecl loadData(Iosapi::Foundation::_di_NSData data, Iosapi::Foundation::_di_NSString MIMEType, Iosapi::Foundation::_di_NSString textEncodingName, Iosapi::Foundation::_di_NSURL baseURL) = 0 ;
	virtual void __cdecl loadHTMLString(Iosapi::Foundation::_di_NSString string_, Iosapi::Foundation::_di_NSURL baseURL) = 0 ;
	virtual void __cdecl loadRequest(Iosapi::Foundation::_di_NSURLRequest request) = 0 ;
	virtual bool __cdecl mediaPlaybackAllowsAirPlay() = 0 ;
	virtual bool __cdecl mediaPlaybackRequiresUserAction() = 0 ;
	virtual void __cdecl reload() = 0 ;
	virtual Iosapi::Foundation::_di_NSURLRequest __cdecl request() = 0 ;
	virtual bool __cdecl scalesPageToFit() = 0 ;
	virtual _di_UIScrollView __cdecl scrollView() = 0 ;
	virtual void __cdecl setAllowsInlineMediaPlayback(bool allowsInlineMediaPlayback) = 0 ;
	virtual void __cdecl setDataDetectorTypes(unsigned long dataDetectorTypes) = 0 ;
	virtual void __cdecl setDelegate(void * delegate) = 0 ;
	virtual void __cdecl setDetectsPhoneNumbers(bool detectsPhoneNumbers) = 0 ;
	virtual void __cdecl setMediaPlaybackAllowsAirPlay(bool mediaPlaybackAllowsAirPlay) = 0 ;
	virtual void __cdecl setMediaPlaybackRequiresUserAction(bool mediaPlaybackRequiresUserAction) = 0 ;
	virtual void __cdecl setScalesPageToFit(bool scalesPageToFit) = 0 ;
	virtual void __cdecl stopLoading() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl stringByEvaluatingJavaScriptFromString(Iosapi::Foundation::_di_NSString script) = 0 ;
};

class PASCALIMPLEMENTATION TUIWebView : public Macapi::Objectivec::TOCGenericImport__2<_di_UIWebViewClass,_di_UIWebView>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UIWebViewClass,_di_UIWebView> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUIWebView(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UIWebViewClass,_di_UIWebView>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUIWebView() { }
	
};


__interface  INTERFACE_UUID("{B81F488C-3A18-4EAC-9CA5-2901848AE908}") UITableViewControllerClass  : public UIViewControllerClass 
{
	
};

__interface  INTERFACE_UUID("{73CE7B2D-0C95-4D75-89CE-1330AD98D89C}") UITableViewController  : public UIViewController 
{
	virtual bool __cdecl clearsSelectionOnViewWillAppear() = 0 ;
	virtual void * __cdecl initWithStyle(long style) = 0 ;
	virtual void __cdecl setClearsSelectionOnViewWillAppear(bool clearsSelectionOnViewWillAppear) = 0 ;
	virtual void __cdecl setTableView(_di_UITableView tableView) = 0 ;
	virtual _di_UITableView __cdecl tableView() = 0 ;
};

class PASCALIMPLEMENTATION TUITableViewController : public Macapi::Objectivec::TOCGenericImport__2<_di_UITableViewControllerClass,_di_UITableViewController>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UITableViewControllerClass,_di_UITableViewController> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUITableViewController(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UITableViewControllerClass,_di_UITableViewController>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUITableViewController() { }
	
};


__interface  INTERFACE_UUID("{094FD093-09E3-4D09-BF6B-7CF1452750AB}") UIToolbarClass  : public UIViewClass 
{
	
};

__interface  INTERFACE_UUID("{90062BBC-88E7-4427-B3A5-8BB14FA23677}") UIToolbar  : public UIView 
{
	virtual _di_UIImage __cdecl backgroundImageForToolbarPosition(unsigned long topOrBottom, long barMetrics) = 0 ;
	virtual long __cdecl barStyle() = 0 ;
	virtual bool __cdecl isTranslucent() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl items() = 0 ;
	virtual void __cdecl setBackgroundImage(_di_UIImage backgroundImage, unsigned long forToolbarPosition, long barMetrics) = 0 ;
	virtual void __cdecl setBarStyle(long barStyle) = 0 ;
	virtual void __cdecl setItems(Iosapi::Foundation::_di_NSArray items) = 0 /* overload */;
	virtual void __cdecl setItems(Iosapi::Foundation::_di_NSArray items, bool animated) = 0 /* overload */;
	HIDESBASE virtual void __cdecl setTintColor(_di_UIColor tintColor) = 0 ;
	virtual void __cdecl setTranslucent(bool translucent) = 0 ;
	HIDESBASE virtual _di_UIColor __cdecl tintColor() = 0 ;
};

class PASCALIMPLEMENTATION TUIToolbar : public Macapi::Objectivec::TOCGenericImport__2<_di_UIToolbarClass,_di_UIToolbar>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UIToolbarClass,_di_UIToolbar> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUIToolbar(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UIToolbarClass,_di_UIToolbar>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUIToolbar() { }
	
};


__interface  INTERFACE_UUID("{945AF986-A933-4C6C-AA37-D742F8FDBB9C}") UITabBarClass  : public UIViewClass 
{
	
};

__interface  INTERFACE_UUID("{661BB52C-5607-48EF-A161-B1EE22B45A2D}") UITabBar  : public UIView 
{
	virtual _di_UIImage __cdecl backgroundImage() = 0 ;
	virtual void __cdecl beginCustomizingItems(Iosapi::Foundation::_di_NSArray items) = 0 ;
	virtual void * __cdecl delegate() = 0 ;
	virtual bool __cdecl endCustomizingAnimated(bool animated) = 0 ;
	virtual bool __cdecl isCustomizing() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl items() = 0 ;
	virtual _di_UIColor __cdecl selectedImageTintColor() = 0 ;
	virtual _di_UITabBarItem __cdecl selectedItem() = 0 ;
	virtual _di_UIImage __cdecl selectionIndicatorImage() = 0 ;
	virtual void __cdecl setBackgroundImage(_di_UIImage backgroundImage) = 0 ;
	virtual void __cdecl setShadowImage(_di_UIImage shadowImage) = 0 ;
	virtual void __cdecl setBarTintColor(_di_UIColor barTintColor) = 0 ;
	virtual void __cdecl setDelegate(void * delegate) = 0 ;
	virtual void __cdecl setItems(Iosapi::Foundation::_di_NSArray items) = 0 /* overload */;
	virtual void __cdecl setItems(Iosapi::Foundation::_di_NSArray items, bool animated) = 0 /* overload */;
	virtual void __cdecl setSelectedImageTintColor(_di_UIColor selectedImageTintColor) = 0 ;
	virtual void __cdecl setSelectedItem(_di_UITabBarItem selectedItem) = 0 ;
	virtual void __cdecl setSelectionIndicatorImage(_di_UIImage selectionIndicatorImage) = 0 ;
	HIDESBASE virtual void __cdecl setTintColor(_di_UIColor tintColor) = 0 ;
	HIDESBASE virtual _di_UIColor __cdecl tintColor() = 0 ;
	virtual _di_UIImage __cdecl shadowImage() = 0 ;
};

class PASCALIMPLEMENTATION TUITabBar : public Macapi::Objectivec::TOCGenericImport__2<_di_UITabBarClass,_di_UITabBar>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UITabBarClass,_di_UITabBar> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUITabBar(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UITabBarClass,_di_UITabBar>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUITabBar() { }
	
};


__interface  INTERFACE_UUID("{22ABB2F0-7BB4-47BB-95F5-FC3F2FDEC1A8}") UITabBarControllerClass  : public UIViewControllerClass 
{
	
};

__interface  INTERFACE_UUID("{C0FB9778-5DE5-4D8E-811E-D27566531604}") UITabBarController  : public UIViewController 
{
	virtual Iosapi::Foundation::_di_NSArray __cdecl customizableViewControllers() = 0 ;
	virtual void * __cdecl delegate() = 0 ;
	virtual _di_UINavigationController __cdecl moreNavigationController() = 0 ;
	virtual unsigned long __cdecl selectedIndex() = 0 ;
	virtual _di_UIViewController __cdecl selectedViewController() = 0 ;
	virtual void __cdecl setCustomizableViewControllers(Iosapi::Foundation::_di_NSArray customizableViewControllers) = 0 ;
	virtual void __cdecl setDelegate(void * delegate) = 0 ;
	virtual void __cdecl setSelectedIndex(unsigned long selectedIndex) = 0 ;
	virtual void __cdecl setSelectedViewController(_di_UIViewController selectedViewController) = 0 ;
	virtual void __cdecl setViewControllers(Iosapi::Foundation::_di_NSArray viewControllers) = 0 /* overload */;
	virtual void __cdecl setViewControllers(Iosapi::Foundation::_di_NSArray viewControllers, bool animated) = 0 /* overload */;
	virtual _di_UITabBar __cdecl tabBar() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl viewControllers() = 0 ;
};

class PASCALIMPLEMENTATION TUITabBarController : public Macapi::Objectivec::TOCGenericImport__2<_di_UITabBarControllerClass,_di_UITabBarController>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UITabBarControllerClass,_di_UITabBarController> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUITabBarController(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UITabBarControllerClass,_di_UITabBarController>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUITabBarController() { }
	
};


__interface  INTERFACE_UUID("{60E6214D-C7C2-43EE-BC3D-B3BA51DDA9C0}") UIWindowClass  : public UIViewClass 
{
	
};

__interface  INTERFACE_UUID("{B2310880-6213-441B-913E-23711AA89558}") UIWindow  : public UIView 
{
	virtual void __cdecl becomeKeyWindow() = 0 ;
	HIDESBASE virtual Iosapi::Foundation::NSPoint __cdecl convertPoint(Iosapi::Foundation::NSPoint point, _di_UIWindow fromWindow) = 0 /* overload */;
	HIDESBASE virtual Iosapi::Foundation::NSRect __cdecl convertRect(Iosapi::Foundation::NSRect rect, _di_UIWindow fromWindow) = 0 /* overload */;
	virtual bool __cdecl isKeyWindow() = 0 ;
	virtual void __cdecl makeKeyAndVisible() = 0 ;
	virtual void __cdecl makeKeyWindow() = 0 ;
	virtual void __cdecl resignKeyWindow() = 0 ;
	virtual _di_UIViewController __cdecl rootViewController() = 0 ;
	virtual _di_UIScreen __cdecl screen() = 0 ;
	virtual void __cdecl sendEvent(_di_UIEvent event) = 0 ;
	virtual void __cdecl setRootViewController(_di_UIViewController rootViewController) = 0 ;
	virtual void __cdecl setScreen(_di_UIScreen screen) = 0 ;
	virtual void __cdecl setWindowLevel(double windowLevel) = 0 ;
	virtual double __cdecl windowLevel() = 0 ;
};

class PASCALIMPLEMENTATION TUIWindow : public Macapi::Objectivec::TOCGenericImport__2<_di_UIWindowClass,_di_UIWindow>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UIWindowClass,_di_UIWindow> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUIWindow(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UIWindowClass,_di_UIWindow>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUIWindow() { }
	
};


__interface  INTERFACE_UUID("{A0AD8EC5-25E9-46F4-9FA0-CF78BF8EA5C7}") UISplitViewControllerClass  : public UIViewControllerClass 
{
	
};

__interface  INTERFACE_UUID("{20EC4A04-B6DE-45A9-96E4-EAAAB5BAE28D}") UISplitViewController  : public UIViewController 
{
	virtual void * __cdecl delegate() = 0 ;
	virtual void __cdecl setDelegate(void * delegate) = 0 ;
	virtual void __cdecl setViewControllers(Iosapi::Foundation::_di_NSArray viewControllers) = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl viewControllers() = 0 ;
};

class PASCALIMPLEMENTATION TUISplitViewController : public Macapi::Objectivec::TOCGenericImport__2<_di_UISplitViewControllerClass,_di_UISplitViewController>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UISplitViewControllerClass,_di_UISplitViewController> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUISplitViewController(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UISplitViewControllerClass,_di_UISplitViewController>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUISplitViewController() { }
	
};


__interface  INTERFACE_UUID("{6BA964FE-C70D-4E0E-A53C-0C56E1A41084}") UINavigationBarClass  : public UIViewClass 
{
	
};

__interface  INTERFACE_UUID("{107EA22D-E942-41DF-8B38-EFD0E6E832A2}") UINavigationBar  : public UIView 
{
	virtual _di_UINavigationItem __cdecl backItem() = 0 ;
	virtual _di_UIImage __cdecl backgroundImageForBarMetrics(long barMetrics) = 0 ;
	virtual long __cdecl barStyle() = 0 ;
	virtual void * __cdecl delegate() = 0 ;
	virtual bool __cdecl isTranslucent() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl items() = 0 ;
	virtual _di_UINavigationItem __cdecl popNavigationItemAnimated(bool animated) = 0 ;
	virtual void __cdecl pushNavigationItem(_di_UINavigationItem item, bool animated) = 0 ;
	virtual void __cdecl setBackgroundImage(_di_UIImage backgroundImage, long forBarMetrics) = 0 ;
	virtual void __cdecl setBarStyle(long barStyle) = 0 ;
	virtual void __cdecl setDelegate(void * delegate) = 0 ;
	virtual void __cdecl setItems(Iosapi::Foundation::_di_NSArray items) = 0 /* overload */;
	virtual void __cdecl setItems(Iosapi::Foundation::_di_NSArray items, bool animated) = 0 /* overload */;
	HIDESBASE virtual void __cdecl setTintColor(_di_UIColor tintColor) = 0 ;
	virtual void __cdecl setTitleTextAttributes(Iosapi::Foundation::_di_NSDictionary titleTextAttributes) = 0 ;
	virtual void __cdecl setTitleVerticalPositionAdjustment(double adjustment, long forBarMetrics) = 0 ;
	virtual void __cdecl setTranslucent(bool translucent) = 0 ;
	HIDESBASE virtual _di_UIColor __cdecl tintColor() = 0 ;
	virtual Iosapi::Foundation::_di_NSDictionary __cdecl titleTextAttributes() = 0 ;
	virtual double __cdecl titleVerticalPositionAdjustmentForBarMetrics(long barMetrics) = 0 ;
	virtual _di_UINavigationItem __cdecl topItem() = 0 ;
};

class PASCALIMPLEMENTATION TUINavigationBar : public Macapi::Objectivec::TOCGenericImport__2<_di_UINavigationBarClass,_di_UINavigationBar>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UINavigationBarClass,_di_UINavigationBar> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUINavigationBar(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UINavigationBarClass,_di_UINavigationBar>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUINavigationBar() { }
	
};


__interface  INTERFACE_UUID("{5E45EE6D-06A9-4392-9832-9570A05E2620}") UILabelClass  : public UIViewClass 
{
	
};

__interface  INTERFACE_UUID("{28363ECE-382C-4450-AEA0-D4E3A7D71CFD}") UILabel  : public UIView 
{
	virtual bool __cdecl adjustsFontSizeToFitWidth() = 0 ;
	virtual long __cdecl baselineAdjustment() = 0 ;
	virtual void __cdecl drawTextInRect(Iosapi::Foundation::NSRect rect) = 0 ;
	virtual _di_UIFont __cdecl font() = 0 ;
	virtual _di_UIColor __cdecl highlightedTextColor() = 0 ;
	virtual bool __cdecl isEnabled() = 0 ;
	virtual bool __cdecl isHighlighted() = 0 ;
	HIDESBASE virtual bool __cdecl isUserInteractionEnabled() = 0 ;
	virtual long __cdecl lineBreakMode() = 0 ;
	virtual double __cdecl minimumFontSize() = 0 ;
	virtual long __cdecl numberOfLines() = 0 ;
	virtual void __cdecl setAdjustsFontSizeToFitWidth(bool adjustsFontSizeToFitWidth) = 0 ;
	virtual void __cdecl setBaselineAdjustment(long baselineAdjustment) = 0 ;
	virtual void __cdecl setEnabled(bool enabled) = 0 ;
	virtual void __cdecl setFont(_di_UIFont font) = 0 ;
	virtual void __cdecl setHighlighted(bool highlighted) = 0 ;
	virtual void __cdecl setHighlightedTextColor(_di_UIColor highlightedTextColor) = 0 ;
	virtual void __cdecl setLineBreakMode(long lineBreakMode) = 0 ;
	virtual void __cdecl setMinimumFontSize(double minimumFontSize) = 0 ;
	virtual void __cdecl setNumberOfLines(long numberOfLines) = 0 ;
	virtual void __cdecl setShadowColor(_di_UIColor shadowColor) = 0 ;
	virtual void __cdecl setShadowOffset(Iosapi::Foundation::NSSize shadowOffset) = 0 ;
	virtual void __cdecl setText(Iosapi::Foundation::_di_NSString text) = 0 ;
	virtual void __cdecl setTextAlignment(long textAlignment) = 0 ;
	virtual void __cdecl setTextColor(_di_UIColor textColor) = 0 ;
	HIDESBASE virtual void __cdecl setUserInteractionEnabled(bool userInteractionEnabled) = 0 ;
	virtual _di_UIColor __cdecl shadowColor() = 0 ;
	virtual Iosapi::Foundation::NSSize __cdecl shadowOffset() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl text() = 0 ;
	virtual long __cdecl textAlignment() = 0 ;
	virtual _di_UIColor __cdecl textColor() = 0 ;
	virtual Iosapi::Foundation::NSRect __cdecl textRectForBounds(Iosapi::Foundation::NSRect bounds, long limitedToNumberOfLines) = 0 ;
};

class PASCALIMPLEMENTATION TUILabel : public Macapi::Objectivec::TOCGenericImport__2<_di_UILabelClass,_di_UILabel>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UILabelClass,_di_UILabel> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUILabel(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UILabelClass,_di_UILabel>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUILabel() { }
	
};


__interface  INTERFACE_UUID("{144258EB-46EF-4CE3-8399-26B585EE5D51}") UINavigationControllerClass  : public UIViewControllerClass 
{
	
};

__interface  INTERFACE_UUID("{BC0A62FD-B83A-4313-AABC-797C7BD64366}") UINavigationController  : public UIViewController 
{
	virtual void * __cdecl delegate() = 0 ;
	virtual void * __cdecl initWithRootViewController(_di_UIViewController rootViewController) = 0 ;
	virtual bool __cdecl isNavigationBarHidden() = 0 ;
	virtual bool __cdecl isToolbarHidden() = 0 ;
	virtual _di_UINavigationBar __cdecl navigationBar() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl popToRootViewControllerAnimated(bool animated) = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl popToViewController(_di_UIViewController viewController, bool animated) = 0 ;
	virtual _di_UIViewController __cdecl popViewControllerAnimated(bool animated) = 0 ;
	virtual void __cdecl pushViewController(_di_UIViewController viewController, bool animated) = 0 ;
	virtual void __cdecl setDelegate(void * delegate) = 0 ;
	virtual void __cdecl setNavigationBarHidden(bool navigationBarHidden) = 0 /* overload */;
	virtual void __cdecl setNavigationBarHidden(bool hidden, bool animated) = 0 /* overload */;
	virtual void __cdecl setToolbarHidden(bool toolbarHidden) = 0 /* overload */;
	virtual void __cdecl setToolbarHidden(bool hidden, bool animated) = 0 /* overload */;
	virtual void __cdecl setViewControllers(Iosapi::Foundation::_di_NSArray viewControllers) = 0 /* overload */;
	virtual void __cdecl setViewControllers(Iosapi::Foundation::_di_NSArray viewControllers, bool animated) = 0 /* overload */;
	virtual _di_UIToolbar __cdecl toolbar() = 0 ;
	virtual _di_UIViewController __cdecl topViewController() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl viewControllers() = 0 ;
	virtual _di_UIViewController __cdecl visibleViewController() = 0 ;
};

class PASCALIMPLEMENTATION TUINavigationController : public Macapi::Objectivec::TOCGenericImport__2<_di_UINavigationControllerClass,_di_UINavigationController>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UINavigationControllerClass,_di_UINavigationController> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUINavigationController(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UINavigationControllerClass,_di_UINavigationController>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUINavigationController() { }
	
};


__interface  INTERFACE_UUID("{216F1E88-1CF4-470A-8AFB-45077FE5A750}") UIPickerViewClass  : public UIViewClass 
{
	
};

__interface  INTERFACE_UUID("{1CBB77B4-19C1-4D9F-9164-4EFCA630CBA8}") UIPickerView  : public UIView 
{
	virtual void * __cdecl dataSource() = 0 ;
	virtual void * __cdecl delegate() = 0 ;
	virtual long __cdecl numberOfComponents() = 0 ;
	virtual long __cdecl numberOfRowsInComponent(long component) = 0 ;
	virtual void __cdecl reloadAllComponents() = 0 ;
	virtual void __cdecl reloadComponent(long component) = 0 ;
	virtual Iosapi::Foundation::NSSize __cdecl rowSizeForComponent(long component) = 0 ;
	virtual void __cdecl selectRow(long row, long inComponent, bool animated) = 0 ;
	virtual long __cdecl selectedRowInComponent(long component) = 0 ;
	virtual void __cdecl setDataSource(void * dataSource) = 0 ;
	virtual void __cdecl setDelegate(void * delegate) = 0 ;
	virtual void __cdecl setShowsSelectionIndicator(bool showsSelectionIndicator) = 0 ;
	virtual bool __cdecl showsSelectionIndicator() = 0 ;
	virtual _di_UIView __cdecl viewForRow(long row, long forComponent) = 0 ;
};

class PASCALIMPLEMENTATION TUIPickerView : public Macapi::Objectivec::TOCGenericImport__2<_di_UIPickerViewClass,_di_UIPickerView>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UIPickerViewClass,_di_UIPickerView> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUIPickerView(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UIPickerViewClass,_di_UIPickerView>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUIPickerView() { }
	
};


__interface  INTERFACE_UUID("{02715341-10EC-43AA-8980-06D16913D9A0}") UIPageViewControllerClass  : public UIViewControllerClass 
{
	
};

__interface  INTERFACE_UUID("{BD8F4370-A8C4-4B5D-9001-CCAB87C3E446}") UIPageViewController  : public UIViewController 
{
	virtual void * __cdecl dataSource() = 0 ;
	virtual void * __cdecl delegate() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl gestureRecognizers() = 0 ;
	virtual void * __cdecl initWithTransitionStyle(long style, long navigationOrientation, Iosapi::Foundation::_di_NSDictionary options) = 0 ;
	virtual bool __cdecl isDoubleSided() = 0 ;
	virtual long __cdecl navigationOrientation() = 0 ;
	virtual void __cdecl setDataSource(void * dataSource) = 0 ;
	virtual void __cdecl setDelegate(void * delegate) = 0 ;
	virtual void __cdecl setDoubleSided(bool doubleSided) = 0 ;
	virtual long __cdecl spineLocation() = 0 ;
	virtual long __cdecl transitionStyle() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl viewControllers() = 0 ;
};

class PASCALIMPLEMENTATION TUIPageViewController : public Macapi::Objectivec::TOCGenericImport__2<_di_UIPageViewControllerClass,_di_UIPageViewController>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UIPageViewControllerClass,_di_UIPageViewController> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUIPageViewController(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UIPageViewControllerClass,_di_UIPageViewController>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUIPageViewController() { }
	
};


__interface  INTERFACE_UUID("{653F48F6-391E-4456-8BEA-619D3DABF160}") UIActivityIndicatorViewClass  : public UIViewClass 
{
	
};

__interface  INTERFACE_UUID("{740BF207-534C-49E0-ACC7-842794A03DF8}") UIActivityIndicatorView  : public UIView 
{
	virtual long __cdecl activityIndicatorViewStyle() = 0 ;
	virtual _di_UIColor __cdecl color() = 0 ;
	virtual bool __cdecl hidesWhenStopped() = 0 ;
	virtual void * __cdecl initWithActivityIndicatorStyle(long style) = 0 ;
	virtual bool __cdecl isAnimating() = 0 ;
	virtual void __cdecl setActivityIndicatorViewStyle(long activityIndicatorViewStyle) = 0 ;
	virtual void __cdecl setColor(_di_UIColor color) = 0 ;
	virtual void __cdecl setHidesWhenStopped(bool hidesWhenStopped) = 0 ;
	virtual void __cdecl startAnimating() = 0 ;
	virtual void __cdecl stopAnimating() = 0 ;
};

class PASCALIMPLEMENTATION TUIActivityIndicatorView : public Macapi::Objectivec::TOCGenericImport__2<_di_UIActivityIndicatorViewClass,_di_UIActivityIndicatorView>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UIActivityIndicatorViewClass,_di_UIActivityIndicatorView> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUIActivityIndicatorView(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UIActivityIndicatorViewClass,_di_UIActivityIndicatorView>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUIActivityIndicatorView() { }
	
};


__interface  INTERFACE_UUID("{97C3C5FB-0D28-4DAB-B06C-41BF18F1667C}") UIActionSheetClass  : public UIViewClass 
{
	
};

__interface  INTERFACE_UUID("{C59B1FB7-4258-4158-B4AE-24D5915FF901}") UIActionSheet  : public UIView 
{
	virtual long __cdecl actionSheetStyle() = 0 ;
	virtual long __cdecl addButtonWithTitle(Iosapi::Foundation::_di_NSString title) = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl buttonTitleAtIndex(long buttonIndex) = 0 ;
	virtual long __cdecl cancelButtonIndex() = 0 ;
	virtual void * __cdecl delegate() = 0 ;
	virtual long __cdecl destructiveButtonIndex() = 0 ;
	virtual void __cdecl dismissWithClickedButtonIndex(long buttonIndex, bool animated) = 0 ;
	virtual long __cdecl firstOtherButtonIndex() = 0 ;
	virtual void * __cdecl initWithTitle(Iosapi::Foundation::_di_NSString title, void * delegate, Iosapi::Foundation::_di_NSString cancelButtonTitle, Iosapi::Foundation::_di_NSString destructiveButtonTitle, Iosapi::Foundation::_di_NSString otherButtonTitles) = 0 ;
	virtual bool __cdecl isVisible() = 0 ;
	virtual long __cdecl numberOfButtons() = 0 ;
	virtual void __cdecl setActionSheetStyle(long actionSheetStyle) = 0 ;
	virtual void __cdecl setCancelButtonIndex(long cancelButtonIndex) = 0 ;
	virtual void __cdecl setDelegate(void * delegate) = 0 ;
	virtual void __cdecl setDestructiveButtonIndex(long destructiveButtonIndex) = 0 ;
	virtual void __cdecl setTitle(Iosapi::Foundation::_di_NSString title) = 0 ;
	virtual void __cdecl showFromBarButtonItem(_di_UIBarButtonItem item, bool animated) = 0 ;
	virtual void __cdecl showFromRect(Iosapi::Foundation::NSRect rect, _di_UIView inView, bool animated) = 0 ;
	virtual void __cdecl showFromTabBar(_di_UITabBar view) = 0 ;
	virtual void __cdecl showFromToolbar(_di_UIToolbar view) = 0 ;
	virtual void __cdecl showInView(_di_UIView view) = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl title() = 0 ;
};

class PASCALIMPLEMENTATION TUIActionSheet : public Macapi::Objectivec::TOCGenericImport__2<_di_UIActionSheetClass,_di_UIActionSheet>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UIActionSheetClass,_di_UIActionSheet> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUIActionSheet(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UIActionSheetClass,_di_UIActionSheet>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUIActionSheet() { }
	
};


__interface  INTERFACE_UUID("{B1BB6463-CC09-487B-9340-607FD6D0863B}") UIActivityViewControllerClass  : public UIViewControllerClass 
{
	
};

__interface  INTERFACE_UUID("{68BE3AE8-E14B-4086-B066-F90C5C527E32}") UIActivityViewController  : public UIViewController 
{
	virtual void * __cdecl initWithActivityItems(Iosapi::Foundation::_di_NSArray activityItems, Iosapi::Foundation::_di_NSArray applicationActivities) = 0 ;
	virtual UIActivityViewControllerCompletionHandler __cdecl completionHandler() = 0 ;
	virtual void __cdecl setCompletionHandler(UIActivityViewControllerCompletionHandler completionHandler) = 0 ;
};

class PASCALIMPLEMENTATION TUIActivityViewController : public Macapi::Objectivec::TOCGenericImport__2<_di_UIActivityViewControllerClass,_di_UIActivityViewController>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UIActivityViewControllerClass,_di_UIActivityViewController> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUIActivityViewController(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UIActivityViewControllerClass,_di_UIActivityViewController>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUIActivityViewController() { }
	
};


__interface  INTERFACE_UUID("{9B52F0F9-605B-46B0-A237-F309ECB3E7E7}") UIAlertViewClass  : public UIViewClass 
{
	
};

__interface  INTERFACE_UUID("{733868C3-9497-4A2E-8BE6-2A764EE2EFFD}") UIAlertView  : public UIView 
{
	virtual long __cdecl addButtonWithTitle(Iosapi::Foundation::_di_NSString title) = 0 ;
	virtual long __cdecl alertViewStyle() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl buttonTitleAtIndex(long buttonIndex) = 0 ;
	virtual long __cdecl cancelButtonIndex() = 0 ;
	virtual void * __cdecl delegate() = 0 ;
	virtual void __cdecl dismissWithClickedButtonIndex(long buttonIndex, bool animated) = 0 ;
	virtual long __cdecl firstOtherButtonIndex() = 0 ;
	virtual void * __cdecl initWithTitle(Iosapi::Foundation::_di_NSString title, Iosapi::Foundation::_di_NSString message, void * delegate, Iosapi::Foundation::_di_NSString cancelButtonTitle, Iosapi::Foundation::_di_NSString otherButtonTitles) = 0 ;
	virtual bool __cdecl isVisible() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl message() = 0 ;
	virtual long __cdecl numberOfButtons() = 0 ;
	virtual void __cdecl setAlertViewStyle(long alertViewStyle) = 0 ;
	virtual void __cdecl setCancelButtonIndex(long cancelButtonIndex) = 0 ;
	virtual void __cdecl setDelegate(void * delegate) = 0 ;
	virtual void __cdecl setMessage(Iosapi::Foundation::_di_NSString message) = 0 ;
	virtual void __cdecl setTitle(Iosapi::Foundation::_di_NSString title) = 0 ;
	virtual void __cdecl show() = 0 ;
	virtual void * __cdecl textFieldAtIndex(long textFieldIndex) = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl title() = 0 ;
};

class PASCALIMPLEMENTATION TUIAlertView : public Macapi::Objectivec::TOCGenericImport__2<_di_UIAlertViewClass,_di_UIAlertView>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UIAlertViewClass,_di_UIAlertView> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUIAlertView(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UIAlertViewClass,_di_UIAlertView>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUIAlertView() { }
	
};


__interface  INTERFACE_UUID("{8AC2E4BA-C422-4312-AAB8-BAEE2F78D837}") UIImageViewClass  : public UIViewClass 
{
	
};

__interface  INTERFACE_UUID("{3C37E7BA-5B35-4AB5-B48B-B308F45EE3C2}") UIImageView  : public UIView 
{
	virtual double __cdecl animationDuration() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl animationImages() = 0 ;
	virtual long __cdecl animationRepeatCount() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl highlightedAnimationImages() = 0 ;
	virtual _di_UIImage __cdecl highlightedImage() = 0 ;
	virtual _di_UIImage __cdecl image() = 0 ;
	virtual void * __cdecl initWithImage(_di_UIImage image) = 0 /* overload */;
	virtual void * __cdecl initWithImage(_di_UIImage image, _di_UIImage highlightedImage) = 0 /* overload */;
	virtual bool __cdecl isAnimating() = 0 ;
	virtual bool __cdecl isHighlighted() = 0 ;
	HIDESBASE virtual bool __cdecl isUserInteractionEnabled() = 0 ;
	virtual void __cdecl setAnimationDuration(double animationDuration) = 0 ;
	virtual void __cdecl setAnimationImages(Iosapi::Foundation::_di_NSArray animationImages) = 0 ;
	virtual void __cdecl setAnimationRepeatCount(long animationRepeatCount) = 0 ;
	virtual void __cdecl setHighlighted(bool highlighted) = 0 ;
	virtual void __cdecl setHighlightedAnimationImages(Iosapi::Foundation::_di_NSArray highlightedAnimationImages) = 0 ;
	virtual void __cdecl setHighlightedImage(_di_UIImage highlightedImage) = 0 ;
	virtual void __cdecl setImage(_di_UIImage image) = 0 ;
	HIDESBASE virtual void __cdecl setUserInteractionEnabled(bool userInteractionEnabled) = 0 ;
	virtual void __cdecl startAnimating() = 0 ;
	virtual void __cdecl stopAnimating() = 0 ;
};

class PASCALIMPLEMENTATION TUIImageView : public Macapi::Objectivec::TOCGenericImport__2<_di_UIImageViewClass,_di_UIImageView>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UIImageViewClass,_di_UIImageView> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUIImageView(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UIImageViewClass,_di_UIImageView>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUIImageView() { }
	
};


__interface  INTERFACE_UUID("{D6494AFD-75F0-4E86-BD61-A28EF623EFE9}") UIControlClass  : public UIViewClass 
{
	
};

__interface  INTERFACE_UUID("{3577D075-1A6B-4614-A590-F4ACB559BDF3}") UIControl  : public UIView 
{
	virtual Iosapi::Foundation::_di_NSArray __cdecl actionsForTarget(void * target, unsigned long forControlEvent) = 0 ;
	virtual void __cdecl addTarget(void * target, void * action, unsigned long forControlEvents) = 0 ;
	virtual unsigned long __cdecl allControlEvents() = 0 ;
	virtual Iosapi::Foundation::_di_NSSet __cdecl allTargets() = 0 ;
	virtual bool __cdecl beginTrackingWithTouch(_di_UITouch touch, _di_UIEvent withEvent) = 0 ;
	virtual void __cdecl cancelTrackingWithEvent(_di_UIEvent event) = 0 ;
	virtual long __cdecl contentHorizontalAlignment() = 0 ;
	virtual long __cdecl contentVerticalAlignment() = 0 ;
	virtual bool __cdecl continueTrackingWithTouch(_di_UITouch touch, _di_UIEvent withEvent) = 0 ;
	virtual void __cdecl endTrackingWithTouch(_di_UITouch touch, _di_UIEvent withEvent) = 0 ;
	virtual bool __cdecl isEnabled() = 0 ;
	virtual bool __cdecl isHighlighted() = 0 ;
	virtual bool __cdecl isSelected() = 0 ;
	virtual bool __cdecl isTouchInside() = 0 ;
	virtual bool __cdecl isTracking() = 0 ;
	virtual void __cdecl removeTarget(void * target, void * action, unsigned long forControlEvents) = 0 ;
	virtual void __cdecl sendActionsForControlEvents(unsigned long controlEvents) = 0 ;
	virtual void __cdecl setContentHorizontalAlignment(long contentHorizontalAlignment) = 0 ;
	virtual void __cdecl setContentVerticalAlignment(long contentVerticalAlignment) = 0 ;
	virtual void __cdecl setEnabled(bool enabled) = 0 ;
	virtual void __cdecl setHighlighted(bool highlighted) = 0 ;
	virtual void __cdecl setSelected(bool selected) = 0 ;
	virtual unsigned long __cdecl state() = 0 ;
};

class PASCALIMPLEMENTATION TUIControl : public Macapi::Objectivec::TOCGenericImport__2<_di_UIControlClass,_di_UIControl>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UIControlClass,_di_UIControl> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUIControl(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UIControlClass,_di_UIControl>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUIControl() { }
	
};


__interface  INTERFACE_UUID("{77B96B73-6425-4D5D-B318-77EB1A22F8B9}") UIProgressViewClass  : public UIViewClass 
{
	
};

__interface  INTERFACE_UUID("{6106703C-52EE-46CE-A99F-1F3CDE1E5906}") UIProgressView  : public UIView 
{
	virtual void * __cdecl initWithProgressViewStyle(long style) = 0 ;
	virtual float __cdecl progress() = 0 ;
	virtual _di_UIImage __cdecl progressImage() = 0 ;
	virtual _di_UIColor __cdecl progressTintColor() = 0 ;
	virtual long __cdecl progressViewStyle() = 0 ;
	virtual void __cdecl setProgress(float progress) = 0 /* overload */;
	virtual void __cdecl setProgress(float progress, bool animated) = 0 /* overload */;
	virtual void __cdecl setProgressImage(_di_UIImage progressImage) = 0 ;
	virtual void __cdecl setProgressTintColor(_di_UIColor progressTintColor) = 0 ;
	virtual void __cdecl setProgressViewStyle(long progressViewStyle) = 0 ;
	virtual void __cdecl setTrackImage(_di_UIImage trackImage) = 0 ;
	virtual void __cdecl setTrackTintColor(_di_UIColor trackTintColor) = 0 ;
	virtual _di_UIImage __cdecl trackImage() = 0 ;
	virtual _di_UIColor __cdecl trackTintColor() = 0 ;
};

class PASCALIMPLEMENTATION TUIProgressView : public Macapi::Objectivec::TOCGenericImport__2<_di_UIProgressViewClass,_di_UIProgressView>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UIProgressViewClass,_di_UIProgressView> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUIProgressView(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UIProgressViewClass,_di_UIProgressView>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUIProgressView() { }
	
};


__interface  INTERFACE_UUID("{9580E8CE-CF16-4AA4-A3AC-57E4BA6E7A30}") UIScrollViewClass  : public UIViewClass 
{
	
};

__interface  INTERFACE_UUID("{AC832A34-44A4-4269-8C3C-47F9F08BC243}") UIScrollView  : public UIView 
{
	virtual bool __cdecl alwaysBounceHorizontal() = 0 ;
	virtual bool __cdecl alwaysBounceVertical() = 0 ;
	virtual bool __cdecl bounces() = 0 ;
	virtual bool __cdecl bouncesZoom() = 0 ;
	virtual bool __cdecl canCancelContentTouches() = 0 ;
	virtual UIEdgeInsets __cdecl contentInset() = 0 ;
	virtual Iosapi::Foundation::NSPoint __cdecl contentOffset() = 0 ;
	virtual Iosapi::Foundation::NSSize __cdecl contentSize() = 0 ;
	virtual double __cdecl decelerationRate() = 0 ;
	virtual bool __cdecl delaysContentTouches() = 0 ;
	virtual void * __cdecl delegate() = 0 ;
	virtual void __cdecl flashScrollIndicators() = 0 ;
	virtual long __cdecl indicatorStyle() = 0 ;
	virtual bool __cdecl isDecelerating() = 0 ;
	virtual bool __cdecl isDirectionalLockEnabled() = 0 ;
	virtual bool __cdecl isDragging() = 0 ;
	virtual bool __cdecl isPagingEnabled() = 0 ;
	virtual bool __cdecl isScrollEnabled() = 0 ;
	virtual bool __cdecl isTracking() = 0 ;
	virtual bool __cdecl isZoomBouncing() = 0 ;
	virtual bool __cdecl isZooming() = 0 ;
	virtual double __cdecl maximumZoomScale() = 0 ;
	virtual double __cdecl minimumZoomScale() = 0 ;
	virtual _di_UIPanGestureRecognizer __cdecl panGestureRecognizer() = 0 ;
	virtual _di_UIPinchGestureRecognizer __cdecl pinchGestureRecognizer() = 0 ;
	virtual UIEdgeInsets __cdecl scrollIndicatorInsets() = 0 ;
	virtual void __cdecl scrollRectToVisible(Iosapi::Foundation::NSRect rect, bool animated) = 0 ;
	virtual bool __cdecl scrollsToTop() = 0 ;
	virtual void __cdecl setAlwaysBounceHorizontal(bool alwaysBounceHorizontal) = 0 ;
	virtual void __cdecl setAlwaysBounceVertical(bool alwaysBounceVertical) = 0 ;
	virtual void __cdecl setBounces(bool bounces) = 0 ;
	virtual void __cdecl setBouncesZoom(bool bouncesZoom) = 0 ;
	virtual void __cdecl setCanCancelContentTouches(bool canCancelContentTouches) = 0 ;
	virtual void __cdecl setContentInset(UIEdgeInsets contentInset) = 0 ;
	virtual void __cdecl setContentOffset(Iosapi::Foundation::NSPoint contentOffset) = 0 /* overload */;
	virtual void __cdecl setContentOffset(Iosapi::Foundation::NSPoint contentOffset, bool animated) = 0 /* overload */;
	virtual void __cdecl setContentSize(Iosapi::Foundation::NSSize contentSize) = 0 ;
	virtual void __cdecl setDecelerationRate(double decelerationRate) = 0 ;
	virtual void __cdecl setDelaysContentTouches(bool delaysContentTouches) = 0 ;
	virtual void __cdecl setDelegate(void * delegate) = 0 ;
	virtual void __cdecl setDirectionalLockEnabled(bool directionalLockEnabled) = 0 ;
	virtual void __cdecl setIndicatorStyle(long indicatorStyle) = 0 ;
	virtual void __cdecl setMaximumZoomScale(double maximumZoomScale) = 0 ;
	virtual void __cdecl setMinimumZoomScale(double minimumZoomScale) = 0 ;
	virtual void __cdecl setPagingEnabled(bool pagingEnabled) = 0 ;
	virtual void __cdecl setScrollEnabled(bool scrollEnabled) = 0 ;
	virtual void __cdecl setScrollIndicatorInsets(UIEdgeInsets scrollIndicatorInsets) = 0 ;
	virtual void __cdecl setScrollsToTop(bool scrollsToTop) = 0 ;
	virtual void __cdecl setShowsHorizontalScrollIndicator(bool showsHorizontalScrollIndicator) = 0 ;
	virtual void __cdecl setShowsVerticalScrollIndicator(bool showsVerticalScrollIndicator) = 0 ;
	virtual void __cdecl setZoomScale(double zoomScale) = 0 /* overload */;
	virtual void __cdecl setZoomScale(double scale, bool animated) = 0 /* overload */;
	virtual bool __cdecl showsHorizontalScrollIndicator() = 0 ;
	virtual bool __cdecl showsVerticalScrollIndicator() = 0 ;
	virtual bool __cdecl touchesShouldBegin(Iosapi::Foundation::_di_NSSet touches, _di_UIEvent withEvent, _di_UIView inContentView) = 0 ;
	virtual bool __cdecl touchesShouldCancelInContentView(_di_UIView view) = 0 ;
	virtual double __cdecl zoomScale() = 0 ;
	virtual void __cdecl zoomToRect(Iosapi::Foundation::NSRect rect, bool animated) = 0 ;
};

class PASCALIMPLEMENTATION TUIScrollView : public Macapi::Objectivec::TOCGenericImport__2<_di_UIScrollViewClass,_di_UIScrollView>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UIScrollViewClass,_di_UIScrollView> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUIScrollView(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UIScrollViewClass,_di_UIScrollView>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUIScrollView() { }
	
};


__interface  INTERFACE_UUID("{7BBEFE7F-28B1-4240-AC66-6AE2492E8B44}") UIReferenceLibraryViewControllerClass  : public UIViewControllerClass 
{
	virtual bool __cdecl dictionaryHasDefinitionForTerm(Iosapi::Foundation::_di_NSString term) = 0 ;
};

__interface  INTERFACE_UUID("{0FCD276F-73FF-4182-92A3-85525608FA41}") UIReferenceLibraryViewController  : public UIViewController 
{
	virtual void * __cdecl initWithTerm(Iosapi::Foundation::_di_NSString term) = 0 ;
};

class PASCALIMPLEMENTATION TUIReferenceLibraryViewController : public Macapi::Objectivec::TOCGenericImport__2<_di_UIReferenceLibraryViewControllerClass,_di_UIReferenceLibraryViewController>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UIReferenceLibraryViewControllerClass,_di_UIReferenceLibraryViewController> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUIReferenceLibraryViewController(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UIReferenceLibraryViewControllerClass,_di_UIReferenceLibraryViewController>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUIReferenceLibraryViewController() { }
	
};


__interface  INTERFACE_UUID("{AFE7DCBF-E3C2-4F71-B5B7-2226161B21B6}") UIPopoverBackgroundViewClass  : public UIViewClass 
{
	virtual double __cdecl arrowBase() = 0 ;
	virtual double __cdecl arrowHeight() = 0 ;
	virtual UIEdgeInsets __cdecl contentViewInsets() = 0 ;
};

__interface  INTERFACE_UUID("{8D894AFF-0033-476E-A2ED-74102DF91BBB}") UIPopoverBackgroundView  : public UIView 
{
	virtual unsigned long __cdecl arrowDirection() = 0 ;
	virtual double __cdecl arrowOffset() = 0 ;
	virtual void __cdecl setArrowDirection(unsigned long arrowDirection) = 0 ;
	virtual void __cdecl setArrowOffset(double arrowOffset) = 0 ;
};

class PASCALIMPLEMENTATION TUIPopoverBackgroundView : public Macapi::Objectivec::TOCGenericImport__2<_di_UIPopoverBackgroundViewClass,_di_UIPopoverBackgroundView>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UIPopoverBackgroundViewClass,_di_UIPopoverBackgroundView> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUIPopoverBackgroundView(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UIPopoverBackgroundViewClass,_di_UIPopoverBackgroundView>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUIPopoverBackgroundView() { }
	
};


__interface  INTERFACE_UUID("{E1BF33AF-6961-436C-BD4B-0E510228697D}") UISearchBarClass  : public UIViewClass 
{
	
};

__interface  INTERFACE_UUID("{62830DEE-15CB-4560-858F-30E62B885A90}") UISearchBar  : public UIView 
{
	virtual long __cdecl autocapitalizationType() = 0 ;
	virtual long __cdecl autocorrectionType() = 0 ;
	virtual _di_UIImage __cdecl backgroundImage() = 0 ;
	virtual long __cdecl barStyle() = 0 ;
	virtual void * __cdecl delegate() = 0 ;
	virtual _di_UIImage __cdecl imageForSearchBarIcon(long icon, unsigned long state) = 0 ;
	virtual bool __cdecl isSearchResultsButtonSelected() = 0 ;
	virtual bool __cdecl isTranslucent() = 0 ;
	virtual long __cdecl keyboardType() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl placeholder() = 0 ;
	virtual UIOffset __cdecl positionAdjustmentForSearchBarIcon(long icon) = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl prompt() = 0 ;
	virtual _di_UIImage __cdecl scopeBarBackgroundImage() = 0 ;
	virtual _di_UIImage __cdecl scopeBarButtonBackgroundImageForState(unsigned long state) = 0 ;
	virtual _di_UIImage __cdecl scopeBarButtonDividerImageForLeftSegmentState(unsigned long leftState, unsigned long rightSegmentState) = 0 ;
	virtual Iosapi::Foundation::_di_NSDictionary __cdecl scopeBarButtonTitleTextAttributesForState(unsigned long state) = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl scopeButtonTitles() = 0 ;
	virtual _di_UIImage __cdecl searchFieldBackgroundImageForState(unsigned long state) = 0 ;
	virtual UIOffset __cdecl searchFieldBackgroundPositionAdjustment() = 0 ;
	virtual UIOffset __cdecl searchTextPositionAdjustment() = 0 ;
	virtual long __cdecl selectedScopeButtonIndex() = 0 ;
	virtual void __cdecl setAutocapitalizationType(long autocapitalizationType) = 0 ;
	virtual void __cdecl setAutocorrectionType(long autocorrectionType) = 0 ;
	virtual void __cdecl setBackgroundImage(_di_UIImage backgroundImage) = 0 ;
	virtual void __cdecl setBarStyle(long barStyle) = 0 ;
	virtual void __cdecl setDelegate(void * delegate) = 0 ;
	virtual void __cdecl setImage(_di_UIImage iconImage, long forSearchBarIcon, unsigned long state) = 0 ;
	virtual void __cdecl setKeyboardType(long keyboardType) = 0 ;
	virtual void __cdecl setPlaceholder(Iosapi::Foundation::_di_NSString placeholder) = 0 ;
	virtual void __cdecl setPositionAdjustment(UIOffset adjustment, long forSearchBarIcon) = 0 ;
	virtual void __cdecl setPrompt(Iosapi::Foundation::_di_NSString prompt) = 0 ;
	virtual void __cdecl setScopeBarBackgroundImage(_di_UIImage scopeBarBackgroundImage) = 0 ;
	virtual void __cdecl setScopeBarButtonBackgroundImage(_di_UIImage backgroundImage, unsigned long forState) = 0 ;
	virtual void __cdecl setScopeBarButtonDividerImage(_di_UIImage dividerImage, unsigned long forLeftSegmentState, unsigned long rightSegmentState) = 0 ;
	virtual void __cdecl setScopeBarButtonTitleTextAttributes(Iosapi::Foundation::_di_NSDictionary attributes, unsigned long forState) = 0 ;
	virtual void __cdecl setScopeButtonTitles(Iosapi::Foundation::_di_NSArray scopeButtonTitles) = 0 ;
	virtual void __cdecl setSearchFieldBackgroundImage(_di_UIImage backgroundImage, unsigned long forState) = 0 ;
	virtual void __cdecl setSearchFieldBackgroundPositionAdjustment(UIOffset searchFieldBackgroundPositionAdjustment) = 0 ;
	virtual void __cdecl setSearchResultsButtonSelected(bool searchResultsButtonSelected) = 0 ;
	virtual void __cdecl setSearchTextPositionAdjustment(UIOffset searchTextPositionAdjustment) = 0 ;
	virtual void __cdecl setSelectedScopeButtonIndex(long selectedScopeButtonIndex) = 0 ;
	virtual void __cdecl setShowsBookmarkButton(bool showsBookmarkButton) = 0 ;
	virtual void __cdecl setShowsCancelButton(bool showsCancelButton) = 0 /* overload */;
	virtual void __cdecl setShowsCancelButton(bool showsCancelButton, bool animated) = 0 /* overload */;
	virtual void __cdecl setShowsScopeBar(bool showsScopeBar) = 0 ;
	virtual void __cdecl setShowsSearchResultsButton(bool showsSearchResultsButton) = 0 ;
	virtual void __cdecl setSpellCheckingType(long spellCheckingType) = 0 ;
	virtual void __cdecl setText(Iosapi::Foundation::_di_NSString text) = 0 ;
	HIDESBASE virtual void __cdecl setTintColor(_di_UIColor tintColor) = 0 ;
	virtual void __cdecl setTranslucent(bool translucent) = 0 ;
	virtual bool __cdecl showsBookmarkButton() = 0 ;
	virtual bool __cdecl showsCancelButton() = 0 ;
	virtual bool __cdecl showsScopeBar() = 0 ;
	virtual bool __cdecl showsSearchResultsButton() = 0 ;
	virtual long __cdecl spellCheckingType() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl text() = 0 ;
	HIDESBASE virtual _di_UIColor __cdecl tintColor() = 0 ;
};

class PASCALIMPLEMENTATION TUISearchBar : public Macapi::Objectivec::TOCGenericImport__2<_di_UISearchBarClass,_di_UISearchBar>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UISearchBarClass,_di_UISearchBar> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUISearchBar(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UISearchBarClass,_di_UISearchBar>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUISearchBar() { }
	
};


__interface  INTERFACE_UUID("{8C880875-52F8-4BE4-AF46-3FB7FF69DD65}") UISearchControllerClass  : public UIViewControllerClass 
{
	
};

__interface  INTERFACE_UUID("{0EBA9215-8451-4533-A1A1-993F074126F2}") UISearchController  : public UIViewController 
{
	virtual void * __cdecl initWithSearchResultsController(_di_UIViewController searchResultsController) = 0 ;
	virtual void __cdecl setSearchResultsUpdater(void * searchResultsUpdater) = 0 ;
	virtual void * __cdecl searchResultsUpdater() = 0 ;
	virtual void __cdecl setActive(bool active) = 0 ;
	virtual bool __cdecl isActive() = 0 ;
	virtual void __cdecl setDelegate(void * delegate) = 0 ;
	virtual void * __cdecl delegate() = 0 ;
	virtual void __cdecl setDimsBackgroundDuringPresentation(bool dimsBackgroundDuringPresentation) = 0 ;
	virtual bool __cdecl dimsBackgroundDuringPresentation() = 0 ;
	virtual void __cdecl setHidesNavigationBarDuringPresentation(bool hidesNavigationBarDuringPresentation) = 0 ;
	virtual bool __cdecl hidesNavigationBarDuringPresentation() = 0 ;
	virtual _di_UIViewController __cdecl searchResultsController() = 0 ;
	virtual _di_UISearchBar __cdecl searchBar() = 0 ;
};

class PASCALIMPLEMENTATION TUISearchController : public Macapi::Objectivec::TOCGenericImport__2<_di_UISearchControllerClass,_di_UISearchController>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UISearchControllerClass,_di_UISearchController> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUISearchController(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UISearchControllerClass,_di_UISearchController>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUISearchController() { }
	
};


typedef void * PUISearchController;

__interface  INTERFACE_UUID("{8C745044-2178-423C-9799-8933FFC7526B}") UIVideoEditorControllerClass  : public UINavigationControllerClass 
{
	virtual bool __cdecl canEditVideoAtPath(Iosapi::Foundation::_di_NSString videoPath) = 0 ;
};

__interface  INTERFACE_UUID("{6098EB7F-17EF-4E74-84AC-5434AAB6CE1F}") UIVideoEditorController  : public UINavigationController 
{
	HIDESBASE virtual void * __cdecl delegate() = 0 ;
	HIDESBASE virtual void __cdecl setDelegate(void * delegate) = 0 ;
	virtual void __cdecl setVideoMaximumDuration(double videoMaximumDuration) = 0 ;
	virtual void __cdecl setVideoPath(Iosapi::Foundation::_di_NSString videoPath) = 0 ;
	virtual void __cdecl setVideoQuality(long videoQuality) = 0 ;
	virtual double __cdecl videoMaximumDuration() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl videoPath() = 0 ;
	virtual long __cdecl videoQuality() = 0 ;
};

class PASCALIMPLEMENTATION TUIVideoEditorController : public Macapi::Objectivec::TOCGenericImport__2<_di_UIVideoEditorControllerClass,_di_UIVideoEditorController>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UIVideoEditorControllerClass,_di_UIVideoEditorController> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUIVideoEditorController(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UIVideoEditorControllerClass,_di_UIVideoEditorController>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUIVideoEditorController() { }
	
};


__interface  INTERFACE_UUID("{183E87F4-3D08-43E6-911A-219EE6D46166}") UIButtonClass  : public UIControlClass 
{
	virtual void * __cdecl buttonWithType(long buttonType) = 0 ;
};

__interface  INTERFACE_UUID("{73F43D61-2EAC-4902-834E-11BBC2B84102}") UIButton  : public UIControl 
{
	virtual bool __cdecl adjustsImageWhenDisabled() = 0 ;
	virtual bool __cdecl adjustsImageWhenHighlighted() = 0 ;
	virtual _di_UIImage __cdecl backgroundImageForState(unsigned long state) = 0 ;
	virtual Iosapi::Foundation::NSRect __cdecl backgroundRectForBounds(Iosapi::Foundation::NSRect bounds) = 0 ;
	virtual long __cdecl buttonType() = 0 ;
	virtual UIEdgeInsets __cdecl contentEdgeInsets() = 0 ;
	virtual Iosapi::Foundation::NSRect __cdecl contentRectForBounds(Iosapi::Foundation::NSRect bounds) = 0 ;
	virtual _di_UIImage __cdecl currentBackgroundImage() = 0 ;
	virtual _di_UIImage __cdecl currentImage() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl currentTitle() = 0 ;
	virtual _di_UIColor __cdecl currentTitleColor() = 0 ;
	virtual _di_UIColor __cdecl currentTitleShadowColor() = 0 ;
	virtual _di_UIFont __cdecl font() = 0 ;
	virtual UIEdgeInsets __cdecl imageEdgeInsets() = 0 ;
	virtual _di_UIImage __cdecl imageForState(unsigned long state) = 0 ;
	virtual Iosapi::Foundation::NSRect __cdecl imageRectForContentRect(Iosapi::Foundation::NSRect contentRect) = 0 ;
	virtual _di_UIImageView __cdecl imageView() = 0 ;
	virtual long __cdecl lineBreakMode() = 0 ;
	virtual bool __cdecl reversesTitleShadowWhenHighlighted() = 0 ;
	virtual void __cdecl setAdjustsImageWhenDisabled(bool adjustsImageWhenDisabled) = 0 ;
	virtual void __cdecl setAdjustsImageWhenHighlighted(bool adjustsImageWhenHighlighted) = 0 ;
	virtual void __cdecl setBackgroundImage(_di_UIImage image, unsigned long forState) = 0 ;
	virtual void __cdecl setContentEdgeInsets(UIEdgeInsets contentEdgeInsets) = 0 ;
	virtual void __cdecl setFont(_di_UIFont font) = 0 ;
	virtual void __cdecl setImage(_di_UIImage image, unsigned long forState) = 0 ;
	virtual void __cdecl setImageEdgeInsets(UIEdgeInsets imageEdgeInsets) = 0 ;
	virtual void __cdecl setLineBreakMode(long lineBreakMode) = 0 ;
	virtual void __cdecl setReversesTitleShadowWhenHighlighted(bool reversesTitleShadowWhenHighlighted) = 0 ;
	virtual void __cdecl setShowsTouchWhenHighlighted(bool showsTouchWhenHighlighted) = 0 ;
	HIDESBASE virtual void __cdecl setTintColor(_di_UIColor tintColor) = 0 ;
	virtual void __cdecl setTitle(Iosapi::Foundation::_di_NSString title, unsigned long forState) = 0 ;
	virtual void __cdecl setTitleColor(_di_UIColor color, unsigned long forState) = 0 ;
	virtual void __cdecl setTitleEdgeInsets(UIEdgeInsets titleEdgeInsets) = 0 ;
	virtual void __cdecl setTitleShadowColor(_di_UIColor color, unsigned long forState) = 0 ;
	virtual void __cdecl setTitleShadowOffset(Iosapi::Foundation::NSSize titleShadowOffset) = 0 ;
	virtual bool __cdecl showsTouchWhenHighlighted() = 0 ;
	HIDESBASE virtual _di_UIColor __cdecl tintColor() = 0 ;
	virtual _di_UIColor __cdecl titleColorForState(unsigned long state) = 0 ;
	virtual UIEdgeInsets __cdecl titleEdgeInsets() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl titleForState(unsigned long state) = 0 ;
	virtual _di_UILabel __cdecl titleLabel() = 0 ;
	virtual Iosapi::Foundation::NSRect __cdecl titleRectForContentRect(Iosapi::Foundation::NSRect contentRect) = 0 ;
	virtual _di_UIColor __cdecl titleShadowColorForState(unsigned long state) = 0 ;
	virtual Iosapi::Foundation::NSSize __cdecl titleShadowOffset() = 0 ;
};

class PASCALIMPLEMENTATION TUIButton : public Macapi::Objectivec::TOCGenericImport__2<_di_UIButtonClass,_di_UIButton>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UIButtonClass,_di_UIButton> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUIButton(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UIButtonClass,_di_UIButton>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUIButton() { }
	
};


__interface  INTERFACE_UUID("{98CFAF41-6DE2-458A-AD1C-3159198C8ABF}") UIStepperClass  : public UIControlClass 
{
	
};

__interface  INTERFACE_UUID("{C6CE3399-B896-4E50-8663-61637BFD791D}") UIStepper  : public UIControl 
{
	virtual bool __cdecl autorepeat() = 0 ;
	virtual bool __cdecl isContinuous() = 0 ;
	virtual double __cdecl maximumValue() = 0 ;
	virtual double __cdecl minimumValue() = 0 ;
	virtual void __cdecl setAutorepeat(bool autorepeat) = 0 ;
	virtual void __cdecl setContinuous(bool continuous) = 0 ;
	virtual void __cdecl setMaximumValue(double maximumValue) = 0 ;
	virtual void __cdecl setMinimumValue(double minimumValue) = 0 ;
	virtual void __cdecl setStepValue(double stepValue) = 0 ;
	virtual void __cdecl setValue(double value) = 0 ;
	virtual void __cdecl setWraps(bool wraps) = 0 ;
	virtual double __cdecl stepValue() = 0 ;
	virtual double __cdecl value() = 0 ;
	virtual bool __cdecl wraps() = 0 ;
};

class PASCALIMPLEMENTATION TUIStepper : public Macapi::Objectivec::TOCGenericImport__2<_di_UIStepperClass,_di_UIStepper>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UIStepperClass,_di_UIStepper> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUIStepper(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UIStepperClass,_di_UIStepper>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUIStepper() { }
	
};


__interface  INTERFACE_UUID("{8F6BB419-10A7-4B89-88D8-A9CD27D427FE}") UISliderClass  : public UIControlClass 
{
	
};

__interface  INTERFACE_UUID("{50F62B14-EA25-41F4-BCC8-00587E789C15}") UISlider  : public UIControl 
{
	virtual _di_UIImage __cdecl currentMaximumTrackImage() = 0 ;
	virtual _di_UIImage __cdecl currentMinimumTrackImage() = 0 ;
	virtual _di_UIImage __cdecl currentThumbImage() = 0 ;
	virtual bool __cdecl isContinuous() = 0 ;
	virtual _di_UIImage __cdecl maximumTrackImageForState(unsigned long state) = 0 ;
	virtual _di_UIColor __cdecl maximumTrackTintColor() = 0 ;
	virtual float __cdecl maximumValue() = 0 ;
	virtual _di_UIImage __cdecl maximumValueImage() = 0 ;
	virtual Iosapi::Foundation::NSRect __cdecl maximumValueImageRectForBounds(Iosapi::Foundation::NSRect bounds) = 0 ;
	virtual _di_UIImage __cdecl minimumTrackImageForState(unsigned long state) = 0 ;
	virtual _di_UIColor __cdecl minimumTrackTintColor() = 0 ;
	virtual float __cdecl minimumValue() = 0 ;
	virtual _di_UIImage __cdecl minimumValueImage() = 0 ;
	virtual Iosapi::Foundation::NSRect __cdecl minimumValueImageRectForBounds(Iosapi::Foundation::NSRect bounds) = 0 ;
	virtual void __cdecl setContinuous(bool continuous) = 0 ;
	virtual void __cdecl setMaximumTrackImage(_di_UIImage image, unsigned long forState) = 0 ;
	virtual void __cdecl setMaximumTrackTintColor(_di_UIColor maximumTrackTintColor) = 0 ;
	virtual void __cdecl setMaximumValue(float maximumValue) = 0 ;
	virtual void __cdecl setMaximumValueImage(_di_UIImage maximumValueImage) = 0 ;
	virtual void __cdecl setMinimumTrackImage(_di_UIImage image, unsigned long forState) = 0 ;
	virtual void __cdecl setMinimumTrackTintColor(_di_UIColor minimumTrackTintColor) = 0 ;
	virtual void __cdecl setMinimumValue(float minimumValue) = 0 ;
	virtual void __cdecl setMinimumValueImage(_di_UIImage minimumValueImage) = 0 ;
	virtual void __cdecl setThumbImage(_di_UIImage image, unsigned long forState) = 0 ;
	virtual void __cdecl setThumbTintColor(_di_UIColor thumbTintColor) = 0 ;
	virtual void __cdecl setValue(float value) = 0 /* overload */;
	virtual void __cdecl setValue(float value, bool animated) = 0 /* overload */;
	virtual _di_UIImage __cdecl thumbImageForState(unsigned long state) = 0 ;
	virtual Iosapi::Foundation::NSRect __cdecl thumbRectForBounds(Iosapi::Foundation::NSRect bounds, Iosapi::Foundation::NSRect trackRect, float value) = 0 ;
	virtual _di_UIColor __cdecl thumbTintColor() = 0 ;
	virtual Iosapi::Foundation::NSRect __cdecl trackRectForBounds(Iosapi::Foundation::NSRect bounds) = 0 ;
	virtual float __cdecl value() = 0 ;
};

class PASCALIMPLEMENTATION TUISlider : public Macapi::Objectivec::TOCGenericImport__2<_di_UISliderClass,_di_UISlider>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UISliderClass,_di_UISlider> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUISlider(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UISliderClass,_di_UISlider>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUISlider() { }
	
};


__interface  INTERFACE_UUID("{60EAB276-F080-4A4B-85CF-3877FADB5459}") UISegmentedControlClass  : public UIControlClass 
{
	
};

__interface  INTERFACE_UUID("{F8025182-9CC0-45A4-BF23-92D349F14062}") UISegmentedControl  : public UIControl 
{
	virtual bool __cdecl apportionsSegmentWidthsByContent() = 0 ;
	virtual _di_UIImage __cdecl backgroundImageForState(unsigned long state, long barMetrics) = 0 ;
	virtual Iosapi::Foundation::NSSize __cdecl contentOffsetForSegmentAtIndex(unsigned long segment) = 0 ;
	virtual UIOffset __cdecl contentPositionAdjustmentForSegmentType(long leftCenterRightOrAlone, long barMetrics) = 0 ;
	virtual _di_UIImage __cdecl dividerImageForLeftSegmentState(unsigned long leftState, unsigned long rightSegmentState, long barMetrics) = 0 ;
	virtual _di_UIImage __cdecl imageForSegmentAtIndex(unsigned long segment) = 0 ;
	virtual void * __cdecl initWithItems(Iosapi::Foundation::_di_NSArray items) = 0 ;
	virtual void __cdecl insertSegmentWithImage(_di_UIImage image, unsigned long atIndex, bool animated) = 0 ;
	virtual void __cdecl insertSegmentWithTitle(Iosapi::Foundation::_di_NSString title, unsigned long atIndex, bool animated) = 0 ;
	virtual bool __cdecl isEnabledForSegmentAtIndex(unsigned long segment) = 0 ;
	virtual bool __cdecl isMomentary() = 0 ;
	virtual unsigned long __cdecl numberOfSegments() = 0 ;
	virtual void __cdecl removeAllSegments() = 0 ;
	virtual void __cdecl removeSegmentAtIndex(unsigned long segment, bool animated) = 0 ;
	virtual long __cdecl segmentedControlStyle() = 0 ;
	virtual long __cdecl selectedSegmentIndex() = 0 ;
	virtual void __cdecl setApportionsSegmentWidthsByContent(bool apportionsSegmentWidthsByContent) = 0 ;
	virtual void __cdecl setBackgroundImage(_di_UIImage backgroundImage, unsigned long forState, long barMetrics) = 0 ;
	virtual void __cdecl setContentOffset(Iosapi::Foundation::NSSize offset, unsigned long forSegmentAtIndex) = 0 ;
	virtual void __cdecl setContentPositionAdjustment(UIOffset adjustment, long forSegmentType, long barMetrics) = 0 ;
	virtual void __cdecl setDividerImage(_di_UIImage dividerImage, unsigned long forLeftSegmentState, unsigned long rightSegmentState, long barMetrics) = 0 ;
	HIDESBASE virtual void __cdecl setEnabled(bool enabled, unsigned long forSegmentAtIndex) = 0 ;
	virtual void __cdecl setImage(_di_UIImage image, unsigned long forSegmentAtIndex) = 0 ;
	virtual void __cdecl setMomentary(bool momentary) = 0 ;
	virtual void __cdecl setSegmentedControlStyle(long segmentedControlStyle) = 0 ;
	virtual void __cdecl setSelectedSegmentIndex(long selectedSegmentIndex) = 0 ;
	HIDESBASE virtual void __cdecl setTintColor(_di_UIColor tintColor) = 0 ;
	virtual void __cdecl setTitle(Iosapi::Foundation::_di_NSString title, unsigned long forSegmentAtIndex) = 0 ;
	virtual void __cdecl setTitleTextAttributes(Iosapi::Foundation::_di_NSDictionary attributes, unsigned long forState) = 0 ;
	virtual void __cdecl setWidth(double width, unsigned long forSegmentAtIndex) = 0 ;
	HIDESBASE virtual _di_UIColor __cdecl tintColor() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl titleForSegmentAtIndex(unsigned long segment) = 0 ;
	virtual Iosapi::Foundation::_di_NSDictionary __cdecl titleTextAttributesForState(unsigned long state) = 0 ;
	virtual double __cdecl widthForSegmentAtIndex(unsigned long segment) = 0 ;
};

class PASCALIMPLEMENTATION TUISegmentedControl : public Macapi::Objectivec::TOCGenericImport__2<_di_UISegmentedControlClass,_di_UISegmentedControl>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UISegmentedControlClass,_di_UISegmentedControl> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUISegmentedControl(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UISegmentedControlClass,_di_UISegmentedControl>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUISegmentedControl() { }
	
};


__interface  INTERFACE_UUID("{FC89C5F2-AEFA-4D4E-AFEC-483F443A167B}") UIDatePickerClass  : public UIControlClass 
{
	
};

__interface  INTERFACE_UUID("{58D30B69-5CB3-4CB1-ABDB-CAC1783256FA}") UIDatePicker  : public UIControl 
{
	virtual Iosapi::Foundation::_di_NSCalendar __cdecl calendar() = 0 ;
	virtual double __cdecl countDownDuration() = 0 ;
	virtual Iosapi::Foundation::_di_NSDate __cdecl date() = 0 ;
	virtual long __cdecl datePickerMode() = 0 ;
	virtual Iosapi::Foundation::_di_NSLocale __cdecl locale() = 0 ;
	virtual Iosapi::Foundation::_di_NSDate __cdecl maximumDate() = 0 ;
	virtual Iosapi::Foundation::_di_NSDate __cdecl minimumDate() = 0 ;
	virtual long __cdecl minuteInterval() = 0 ;
	virtual void __cdecl setCalendar(Iosapi::Foundation::_di_NSCalendar calendar) = 0 ;
	virtual void __cdecl setCountDownDuration(double countDownDuration) = 0 ;
	virtual void __cdecl setDate(Iosapi::Foundation::_di_NSDate date) = 0 /* overload */;
	virtual void __cdecl setDate(Iosapi::Foundation::_di_NSDate date, bool animated) = 0 /* overload */;
	virtual void __cdecl setDatePickerMode(long datePickerMode) = 0 ;
	virtual void __cdecl setLocale(Iosapi::Foundation::_di_NSLocale locale) = 0 ;
	virtual void __cdecl setMaximumDate(Iosapi::Foundation::_di_NSDate maximumDate) = 0 ;
	virtual void __cdecl setMinimumDate(Iosapi::Foundation::_di_NSDate minimumDate) = 0 ;
	virtual void __cdecl setMinuteInterval(long minuteInterval) = 0 ;
	virtual void __cdecl setTimeZone(Iosapi::Foundation::_di_NSTimeZone timeZone) = 0 ;
	virtual Iosapi::Foundation::_di_NSTimeZone __cdecl timeZone() = 0 ;
};

class PASCALIMPLEMENTATION TUIDatePicker : public Macapi::Objectivec::TOCGenericImport__2<_di_UIDatePickerClass,_di_UIDatePicker>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UIDatePickerClass,_di_UIDatePicker> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUIDatePicker(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UIDatePickerClass,_di_UIDatePicker>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUIDatePicker() { }
	
};


__interface  INTERFACE_UUID("{2D02A274-7CE8-409C-85F5-6E6EDA6A5C92}") UIPageControlClass  : public UIControlClass 
{
	
};

__interface  INTERFACE_UUID("{E99DE502-9B21-4E38-B1F1-A85B357D0E65}") UIPageControl  : public UIControl 
{
	virtual long __cdecl currentPage() = 0 ;
	virtual bool __cdecl defersCurrentPageDisplay() = 0 ;
	virtual bool __cdecl hidesForSinglePage() = 0 ;
	virtual long __cdecl numberOfPages() = 0 ;
	virtual void __cdecl setCurrentPage(long currentPage) = 0 ;
	virtual void __cdecl setDefersCurrentPageDisplay(bool defersCurrentPageDisplay) = 0 ;
	virtual void __cdecl setHidesForSinglePage(bool hidesForSinglePage) = 0 ;
	virtual void __cdecl setNumberOfPages(long numberOfPages) = 0 ;
	virtual Iosapi::Foundation::NSSize __cdecl sizeForNumberOfPages(long pageCount) = 0 ;
	virtual void __cdecl updateCurrentPageDisplay() = 0 ;
};

class PASCALIMPLEMENTATION TUIPageControl : public Macapi::Objectivec::TOCGenericImport__2<_di_UIPageControlClass,_di_UIPageControl>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UIPageControlClass,_di_UIPageControl> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUIPageControl(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UIPageControlClass,_di_UIPageControl>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUIPageControl() { }
	
};


__interface  INTERFACE_UUID("{995609A0-E3FC-4083-AD2C-73EBB6DD2686}") UIImagePickerControllerClass  : public UINavigationControllerClass 
{
	virtual Iosapi::Foundation::_di_NSArray __cdecl availableCaptureModesForCameraDevice(long cameraDevice) = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl availableMediaTypesForSourceType(long sourceType) = 0 ;
	virtual bool __cdecl isCameraDeviceAvailable(long cameraDevice) = 0 ;
	virtual bool __cdecl isFlashAvailableForCameraDevice(long cameraDevice) = 0 ;
	virtual bool __cdecl isSourceTypeAvailable(long sourceType) = 0 ;
};

__interface  INTERFACE_UUID("{D53CD2AC-4FB2-454C-9BDB-BC4858778909}") UIImagePickerController  : public UINavigationController 
{
	virtual bool __cdecl allowsEditing() = 0 ;
	virtual bool __cdecl allowsImageEditing() = 0 ;
	virtual long __cdecl cameraCaptureMode() = 0 ;
	virtual long __cdecl cameraDevice() = 0 ;
	virtual long __cdecl cameraFlashMode() = 0 ;
	virtual _di_UIView __cdecl cameraOverlayView() = 0 ;
	virtual Iosapi::Coregraphics::CGAffineTransform __cdecl cameraViewTransform() = 0 ;
	HIDESBASE virtual void * __cdecl delegate() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl mediaTypes() = 0 ;
	virtual void __cdecl setAllowsEditing(bool allowsEditing) = 0 ;
	virtual void __cdecl setAllowsImageEditing(bool allowsImageEditing) = 0 ;
	virtual void __cdecl setCameraCaptureMode(long cameraCaptureMode) = 0 ;
	virtual void __cdecl setCameraDevice(long cameraDevice) = 0 ;
	virtual void __cdecl setCameraFlashMode(long cameraFlashMode) = 0 ;
	virtual void __cdecl setCameraOverlayView(_di_UIView cameraOverlayView) = 0 ;
	virtual void __cdecl setCameraViewTransform(Iosapi::Coregraphics::CGAffineTransform cameraViewTransform) = 0 ;
	HIDESBASE virtual void __cdecl setDelegate(void * delegate) = 0 ;
	virtual void __cdecl setMediaTypes(Iosapi::Foundation::_di_NSArray mediaTypes) = 0 ;
	virtual void __cdecl setShowsCameraControls(bool showsCameraControls) = 0 ;
	virtual void __cdecl setSourceType(long sourceType) = 0 ;
	virtual void __cdecl setVideoMaximumDuration(double videoMaximumDuration) = 0 ;
	virtual void __cdecl setVideoQuality(long videoQuality) = 0 ;
	virtual bool __cdecl showsCameraControls() = 0 ;
	virtual long __cdecl sourceType() = 0 ;
	virtual bool __cdecl startVideoCapture() = 0 ;
	virtual void __cdecl stopVideoCapture() = 0 ;
	virtual void __cdecl takePicture() = 0 ;
	virtual double __cdecl videoMaximumDuration() = 0 ;
	virtual long __cdecl videoQuality() = 0 ;
};

class PASCALIMPLEMENTATION TUIImagePickerController : public Macapi::Objectivec::TOCGenericImport__2<_di_UIImagePickerControllerClass,_di_UIImagePickerController>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UIImagePickerControllerClass,_di_UIImagePickerController> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUIImagePickerController(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UIImagePickerControllerClass,_di_UIImagePickerController>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUIImagePickerController() { }
	
};


__interface  INTERFACE_UUID("{9D221886-49F8-4614-A1DF-6EAACB1EDE92}") UITextViewClass  : public UIScrollViewClass 
{
	
};

__interface  INTERFACE_UUID("{1FAC7927-055D-4132-A7D3-913E303A4D6E}") UITextView  : public UIScrollView 
{
	virtual unsigned long __cdecl dataDetectorTypes() = 0 ;
	HIDESBASE virtual void * __cdecl delegate() = 0 ;
	virtual _di_UIFont __cdecl font() = 0 ;
	virtual bool __cdecl hasText() = 0 ;
	HIDESBASE virtual _di_UIView __cdecl inputAccessoryView() = 0 ;
	HIDESBASE virtual _di_UIView __cdecl inputView() = 0 ;
	virtual bool __cdecl isEditable() = 0 ;
	virtual void __cdecl scrollRangeToVisible(Iosapi::Foundation::NSRange range) = 0 ;
	virtual Iosapi::Foundation::NSRange __cdecl selectedRange() = 0 ;
	virtual void __cdecl setDataDetectorTypes(unsigned long dataDetectorTypes) = 0 ;
	HIDESBASE virtual void __cdecl setDelegate(void * delegate) = 0 ;
	virtual void __cdecl setEditable(bool editable) = 0 ;
	virtual void __cdecl setFont(_di_UIFont font) = 0 ;
	virtual void __cdecl setInputAccessoryView(_di_UIView inputAccessoryView) = 0 ;
	virtual void __cdecl setInputView(_di_UIView inputView) = 0 ;
	virtual void __cdecl setSelectedRange(Iosapi::Foundation::NSRange selectedRange) = 0 ;
	virtual void __cdecl setText(Iosapi::Foundation::_di_NSString text) = 0 ;
	virtual void __cdecl setTextAlignment(long textAlignment) = 0 ;
	virtual void __cdecl setTextColor(_di_UIColor textColor) = 0 ;
	virtual void __cdecl setTextContainerInset(UIEdgeInsets textContainerInset) = 0 ;
	virtual void __cdecl setAttributedText(Iosapi::Foundation::_di_NSAttributedString attributedText) = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl text() = 0 ;
	virtual long __cdecl textAlignment() = 0 ;
	virtual _di_UIColor __cdecl textColor() = 0 ;
	virtual UIEdgeInsets __cdecl textContainerInset() = 0 ;
	virtual Iosapi::Foundation::_di_NSAttributedString __cdecl attributedText() = 0 ;
	virtual long __cdecl autocapitalizationType() = 0 ;
	virtual long __cdecl autocorrectionType() = 0 ;
	virtual bool __cdecl enablesReturnKeyAutomatically() = 0 ;
	virtual bool __cdecl isSecureTextEntry() = 0 ;
	virtual long __cdecl keyboardAppearance() = 0 ;
	virtual long __cdecl keyboardType() = 0 ;
	virtual long __cdecl returnKeyType() = 0 ;
	virtual void __cdecl setAutocapitalizationType(long autocapitalizationType) = 0 ;
	virtual void __cdecl setAutocorrectionType(long autocorrectionType) = 0 ;
	virtual void __cdecl setEnablesReturnKeyAutomatically(bool enablesReturnKeyAutomatically) = 0 ;
	virtual void __cdecl setKeyboardAppearance(long keyboardAppearance) = 0 ;
	virtual void __cdecl setKeyboardType(long keyboardType) = 0 ;
	virtual void __cdecl setReturnKeyType(long returnKeyType) = 0 ;
	virtual void __cdecl setSecureTextEntry(bool secureTextEntry) = 0 ;
	virtual void __cdecl setSpellCheckingType(int spellCheckingType) = 0 ;
	virtual int __cdecl spellCheckingType() = 0 ;
	virtual void __cdecl setSelectedTextRange(_di_UITextRange SelectedTextRange) = 0 ;
	virtual void __cdecl unmarkText() = 0 ;
	virtual _di_UITextRange __cdecl markedTextRange() = 0 ;
};

class PASCALIMPLEMENTATION TUITextView : public Macapi::Objectivec::TOCGenericImport__2<_di_UITextViewClass,_di_UITextView>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UITextViewClass,_di_UITextView> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUITextView(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UITextViewClass,_di_UITextView>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUITextView() { }
	
};


__interface  INTERFACE_UUID("{BF60A5F6-0765-4BDF-9328-072D3CB9C92B}") UISwitchClass  : public UIControlClass 
{
	
};

__interface  INTERFACE_UUID("{CC5A762A-FE08-46A3-B994-444FC01C936D}") UISwitch  : public UIControl 
{
	HIDESBASE virtual void * __cdecl initWithFrame(Iosapi::Foundation::NSRect frame) = 0 ;
	virtual bool __cdecl isOn() = 0 ;
	virtual _di_UIColor __cdecl onTintColor() = 0 ;
	virtual void __cdecl setOn(bool on) = 0 /* overload */;
	virtual void __cdecl setOn(bool on, bool animated) = 0 /* overload */;
	virtual void __cdecl setOnTintColor(_di_UIColor onTintColor) = 0 ;
};

class PASCALIMPLEMENTATION TUISwitch : public Macapi::Objectivec::TOCGenericImport__2<_di_UISwitchClass,_di_UISwitch>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UISwitchClass,_di_UISwitch> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUISwitch(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UISwitchClass,_di_UISwitch>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUISwitch() { }
	
};


__interface  INTERFACE_UUID("{EEFD40E4-3A92-4775-BF34-728C122AF10F}") UIActionSheetDelegate  : public Macapi::Objectivec::IObjectiveC 
{
	virtual void __cdecl actionSheet(_di_UIActionSheet actionSheet, long clickedButtonAtIndex) = 0 ;
	virtual void __cdecl actionSheetCancel(_di_UIActionSheet actionSheet) = 0 ;
	virtual void __cdecl didPresentActionSheet(_di_UIActionSheet actionSheet) = 0 ;
	virtual void __cdecl willPresentActionSheet(_di_UIActionSheet actionSheet) = 0 ;
};

__interface  INTERFACE_UUID("{A52A64A0-AA7E-422E-B7A4-8EFCF2C20A49}") UIAlertViewDelegate  : public Macapi::Objectivec::IObjectiveC 
{
	virtual void __cdecl alertView(_di_UIAlertView alertView, long clickedButtonAtIndex) = 0 /* overload */;
	virtual void __cdecl alertViewCancel(_di_UIAlertView alertView) = 0 ;
	virtual void __cdecl didPresentAlertView(_di_UIAlertView alertView) = 0 ;
	virtual void __cdecl alertViewDidDismissWithButtonIndex(_di_UIAlertView alertView, long didDismissWithButtonIndex) = 0 ;
};

__interface  INTERFACE_UUID("{C0474DD7-D5B4-462D-9A32-577497307259}") UIApplicationDelegate  : public Macapi::Objectivec::IObjectiveC 
{
	virtual void __cdecl application(_di_UIApplication Sender, Iosapi::Foundation::NSRect didChangeStatusBarFrame) = 0 /* overload */;
	virtual void __cdecl application(_di_UIApplication Sender, long didChangeStatusBarOrientation) = 0 /* overload */;
	virtual void __cdecl application(_di_UIApplication Sender, Iosapi::Foundation::_di_NSError didFailToRegisterForRemoteNotificationsWithError) = 0 /* overload */;
	virtual bool __cdecl application(_di_UIApplication Sender, Iosapi::Foundation::_di_NSDictionary didFinishLaunchingWithOptions) = 0 /* overload */;
	virtual void __cdecl application(_di_UIApplication Sender, _di_UILocalNotification didReceiveLocalNotification) = 0 /* overload */;
	virtual void __cdecl application(_di_UIApplication Sender, Iosapi::Foundation::_di_NSData didRegisterForRemoteNotificationsWithDeviceToken) = 0 /* overload */;
	virtual bool __cdecl application(_di_UIApplication Sender, Iosapi::Foundation::_di_NSURL handleOpenURL) = 0 /* overload */;
	virtual bool __cdecl application(_di_UIApplication Sender, Iosapi::Foundation::_di_NSURL openURL, Iosapi::Foundation::_di_NSString sourceApplication, void * annotation) = 0 /* overload */;
	virtual void __cdecl application(_di_UIApplication Sender, long willChangeStatusBarOrientation, double duration) = 0 /* overload */;
	virtual void __cdecl applicationDidBecomeActive(_di_UIApplication Sender) = 0 ;
	virtual void __cdecl applicationDidEnterBackground(_di_UIApplication Sender) = 0 ;
	virtual void __cdecl applicationDidReceiveMemoryWarning(_di_UIApplication Sender) = 0 ;
	virtual void __cdecl applicationProtectedDataDidBecomeAvailable(_di_UIApplication Sender) = 0 ;
	virtual void __cdecl applicationProtectedDataWillBecomeUnavailable(_di_UIApplication Sender) = 0 ;
	virtual void __cdecl applicationSignificantTimeChange(_di_UIApplication Sender) = 0 ;
	virtual void __cdecl applicationWillEnterForeground(_di_UIApplication Sender) = 0 ;
	virtual void __cdecl applicationWillResignActive(_di_UIApplication Sender) = 0 ;
	virtual void __cdecl applicationWillTerminate(_di_UIApplication Sender) = 0 ;
	virtual void __cdecl setWindow(_di_UIWindow window) = 0 ;
	virtual _di_UIWindow __cdecl window() = 0 ;
	virtual void __cdecl applicationDidRegisterUserNotificationSettings(_di_UIApplication application, _di_UIUserNotificationSettings didRegisterUserNotificationSettings) = 0 ;
	virtual void __cdecl applicationDidRegisterForRemoteNotificationsWithDeviceToken(_di_UIApplication application, Iosapi::Foundation::_di_NSData didRegisterForRemoteNotificationsWithDeviceToken) = 0 ;
	virtual void __cdecl applicationDidFailToRegisterForRemoteNotificationsWithError(_di_UIApplication application, Iosapi::Foundation::_di_NSError didFailToRegisterForRemoteNotificationsWithError) = 0 ;
	virtual void __cdecl applicationDidReceiveRemoteNotification(_di_UIApplication application, Iosapi::Foundation::_di_NSDictionary didReceiveRemoteNotification) = 0 ;
	virtual void __cdecl applicationDidReceiveLocalNotification(_di_UIApplication application, _di_UILocalNotification didReceiveLocalNotification) = 0 ;
};

__interface  INTERFACE_UUID("{96522BE4-CA33-4F69-9581-494DFD050D01}") UIGestureRecognizerDelegate  : public Macapi::Objectivec::IObjectiveC 
{
	virtual bool __cdecl gestureRecognizer(_di_UIGestureRecognizer gestureRecognizer, _di_UITouch shouldReceiveTouch) = 0 /* overload */;
	virtual bool __cdecl gestureRecognizer(_di_UIGestureRecognizer gestureRecognizer, _di_UIGestureRecognizer shouldRecognizeSimultaneouslyWithGestureRecognizer) = 0 /* overload */;
	virtual bool __cdecl gestureRecognizerShouldBegin(_di_UIGestureRecognizer gestureRecognizer) = 0 ;
};

__interface  INTERFACE_UUID("{EF6254E7-276D-41B4-8374-7C68142C4613}") UIImagePickerControllerDelegate  : public Macapi::Objectivec::IObjectiveC 
{
	virtual void __cdecl imagePickerController(_di_UIImagePickerController picker, _di_UIImage didFinishPickingImage, Iosapi::Foundation::_di_NSDictionary editingInfo) = 0 /* overload */;
	virtual void __cdecl imagePickerController(_di_UIImagePickerController picker, Iosapi::Foundation::_di_NSDictionary didFinishPickingMediaWithInfo) = 0 /* overload */;
	virtual void __cdecl imagePickerControllerDidCancel(_di_UIImagePickerController picker) = 0 ;
};

__interface  INTERFACE_UUID("{0FA66D5F-4FE4-47A6-B326-3E5AC9D191B0}") UIPickerViewDataSource  : public Macapi::Objectivec::IObjectiveC 
{
	virtual long __cdecl numberOfComponentsInPickerView(_di_UIPickerView pickerView) = 0 ;
	virtual long __cdecl pickerView(_di_UIPickerView pickerView, long numberOfRowsInComponent) = 0 ;
};

__interface  INTERFACE_UUID("{FAB79BDD-7094-41B0-B4C6-AF6C261EED91}") UIPickerViewDelegate  : public Macapi::Objectivec::IObjectiveC 
{
	virtual Iosapi::Foundation::_di_NSString __cdecl pickerView(_di_UIPickerView pickerView, long titleForRow, long forComponent) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{AA90B09A-9499-44CF-8B0E-31608EB2C548}") UIPopoverControllerDelegate  : public Macapi::Objectivec::IObjectiveC 
{
	virtual void __cdecl popoverControllerDidDismissPopover(_di_UIPopoverController popoverController) = 0 ;
	virtual bool __cdecl popoverControllerShouldDismissPopover(_di_UIPopoverController popoverController) = 0 ;
};

__interface  INTERFACE_UUID("{5449FDE1-9A5D-4C67-BC30-512B07AD2716}") UITextSelecting  : public Macapi::Objectivec::IObjectiveC 
{
	
};

__interface  INTERFACE_UUID("{B76C73F8-2740-4580-9987-A040C245441A}") UITextFieldDelegate  : public Macapi::Objectivec::IObjectiveC 
{
	virtual bool __cdecl textField(_di_UITextField textField, Iosapi::Foundation::NSRange shouldChangeCharactersInRange, Iosapi::Foundation::_di_NSString replacementString) = 0 ;
	virtual void __cdecl textFieldDidBeginEditing(_di_UITextField textField) = 0 ;
	virtual void __cdecl textFieldDidEndEditing(_di_UITextField textField) = 0 ;
	virtual bool __cdecl textFieldShouldBeginEditing(_di_UITextField textField) = 0 ;
	virtual bool __cdecl textFieldShouldClear(_di_UITextField textField) = 0 ;
	virtual bool __cdecl textFieldShouldEndEditing(_di_UITextField textField) = 0 ;
	virtual bool __cdecl textFieldShouldReturn(_di_UITextField textField) = 0 ;
};

__interface  INTERFACE_UUID("{339F9183-3915-4915-88F4-1C0BAD43DEA8}") UITextInputTraits  : public Macapi::Objectivec::IObjectiveC 
{
	virtual long __cdecl autocapitalizationType() = 0 ;
	virtual long __cdecl autocorrectionType() = 0 ;
	virtual bool __cdecl enablesReturnKeyAutomatically() = 0 ;
	virtual bool __cdecl isSecureTextEntry() = 0 ;
	virtual long __cdecl keyboardAppearance() = 0 ;
	virtual long __cdecl keyboardType() = 0 ;
	virtual long __cdecl returnKeyType() = 0 ;
	virtual void __cdecl setAutocapitalizationType(long autocapitalizationType) = 0 ;
	virtual void __cdecl setAutocorrectionType(long autocorrectionType) = 0 ;
	virtual void __cdecl setEnablesReturnKeyAutomatically(bool enablesReturnKeyAutomatically) = 0 ;
	virtual void __cdecl setKeyboardAppearance(long keyboardAppearance) = 0 ;
	virtual void __cdecl setKeyboardType(long keyboardType) = 0 ;
	virtual void __cdecl setReturnKeyType(long returnKeyType) = 0 ;
	virtual void __cdecl setSecureTextEntry(bool secureTextEntry) = 0 ;
	virtual void __cdecl setSpellCheckingType(long spellCheckingType) = 0 ;
	virtual long __cdecl spellCheckingType() = 0 ;
};

__interface  INTERFACE_UUID("{EC035971-A21F-43C6-ABF7-DB5973705897}") UIKeyInput  : public UITextInputTraits 
{
	virtual void __cdecl deleteBackward() = 0 ;
	virtual bool __cdecl hasText() = 0 ;
	virtual void __cdecl insertText(Iosapi::Foundation::_di_NSString text) = 0 ;
};

__interface  INTERFACE_UUID("{2DF76AA7-B045-44A4-8476-894BA616585C}") UITextInput  : public UIKeyInput 
{
	virtual long __cdecl baseWritingDirectionForPosition(_di_UITextPosition position, long inDirection) = 0 ;
	virtual _di_UITextPosition __cdecl beginningOfDocument() = 0 ;
	virtual Iosapi::Foundation::NSRect __cdecl caretRectForPosition(_di_UITextPosition position) = 0 ;
	virtual _di_UITextRange __cdecl characterRangeAtPoint(Iosapi::Foundation::NSPoint point) = 0 ;
	virtual _di_UITextRange __cdecl characterRangeByExtendingPosition(_di_UITextPosition position, long inDirection) = 0 ;
	virtual _di_UITextPosition __cdecl closestPositionToPoint(Iosapi::Foundation::NSPoint point) = 0 /* overload */;
	virtual _di_UITextPosition __cdecl closestPositionToPoint(Iosapi::Foundation::NSPoint point, _di_UITextRange withinRange) = 0 /* overload */;
	virtual long __cdecl comparePosition(_di_UITextPosition position, _di_UITextPosition toPosition) = 0 ;
	virtual _di_UITextPosition __cdecl endOfDocument() = 0 ;
	virtual Iosapi::Foundation::NSRect __cdecl firstRectForRange(_di_UITextRange range) = 0 ;
	virtual void * __cdecl inputDelegate() = 0 ;
	virtual _di_UITextRange __cdecl markedTextRange() = 0 ;
	virtual Iosapi::Foundation::_di_NSDictionary __cdecl markedTextStyle() = 0 ;
	virtual long __cdecl offsetFromPosition(_di_UITextPosition from, _di_UITextPosition toPosition) = 0 ;
	virtual _di_UITextPosition __cdecl positionFromPosition(_di_UITextPosition position, long inDirection, long offset) = 0 /* overload */;
	virtual _di_UITextPosition __cdecl positionFromPosition(_di_UITextPosition position, long offset) = 0 /* overload */;
	virtual _di_UITextPosition __cdecl positionWithinRange(_di_UITextRange range, long farthestInDirection) = 0 ;
	virtual void __cdecl replaceRange(_di_UITextRange range, Iosapi::Foundation::_di_NSString withText) = 0 ;
	virtual _di_UITextRange __cdecl selectedTextRange() = 0 ;
	virtual void __cdecl setBaseWritingDirection(long writingDirection, _di_UITextRange forRange) = 0 ;
	virtual void __cdecl setInputDelegate(_di_UITextInputDelegate inputDelegate) = 0 ;
	virtual void __cdecl setMarkedText(Iosapi::Foundation::_di_NSString markedText, Iosapi::Foundation::NSRange selectedRange) = 0 ;
	virtual void __cdecl setMarkedTextStyle(Iosapi::Foundation::_di_NSDictionary markedTextStyle) = 0 ;
	virtual void __cdecl setSelectedTextRange(_di_UITextRange selectedTextRange) = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl textInRange(_di_UITextRange range) = 0 ;
	virtual _di_UITextRange __cdecl textRangeFromPosition(_di_UITextPosition fromPosition, _di_UITextPosition toPosition) = 0 ;
	virtual void * __cdecl tokenizer() = 0 ;
	virtual void __cdecl unmarkText() = 0 ;
	virtual void __cdecl insertDictationResult(Iosapi::Foundation::_di_NSArray dictationResult) = 0 ;
	virtual void * __cdecl insertDictationResultPlaceholder() = 0 ;
	virtual Iosapi::Foundation::NSRect __cdecl frameForDictationResultPlaceholder(void * placeholder) = 0 ;
	virtual void __cdecl removeDictationResultPlaceholder(void * placeholder, bool willInsertResult) = 0 ;
};

__interface  INTERFACE_UUID("{25E7C20B-68A2-4011-9D7F-B97647BD48C0}") UIWebViewDelegate  : public Macapi::Objectivec::IObjectiveC 
{
	virtual void __cdecl webView(_di_UIWebView webView, Iosapi::Foundation::_di_NSError didFailLoadWithError) = 0 /* overload */;
	virtual bool __cdecl webView(_di_UIWebView webView, Iosapi::Foundation::_di_NSURLRequest shouldStartLoadWithRequest, long navigationType) = 0 /* overload */;
	virtual void __cdecl webViewDidFinishLoad(_di_UIWebView webView) = 0 ;
	virtual void __cdecl webViewDidStartLoad(_di_UIWebView webView) = 0 ;
};

__interface  INTERFACE_UUID("{D3443E1C-4B13-46E0-B5ED-4D36EE9D584A}") UIMotionEffectClass  : public Iosapi::Quartzcore::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{6557C96B-FEE8-492C-9001-728428F1EDA4}") UIMotionEffect  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::_di_NSDictionary __cdecl keyPathsAndRelativeValuesForViewerOffset(UIOffset viewerOffset) = 0 ;
};

class PASCALIMPLEMENTATION TUIMotionEffect : public Macapi::Objectivec::TOCGenericImport__2<_di_UIMotionEffectClass,_di_UIMotionEffect>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UIMotionEffectClass,_di_UIMotionEffect> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUIMotionEffect(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UIMotionEffectClass,_di_UIMotionEffect>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUIMotionEffect() { }
	
};


__interface  INTERFACE_UUID("{EF7B089F-A484-44E2-85A1-B0BAFCB31DAC}") UITextFieldClass  : public UIControlClass 
{
	
};

__interface  INTERFACE_UUID("{1BCFFC8A-8744-4A3F-A441-DB7B2124AB52}") UITextField  : public UIControl 
{
	virtual bool __cdecl adjustsFontSizeToFitWidth() = 0 ;
	virtual _di_UIImage __cdecl background() = 0 ;
	virtual Iosapi::Foundation::NSRect __cdecl borderRectForBounds(Iosapi::Foundation::NSRect bounds) = 0 ;
	virtual long __cdecl borderStyle() = 0 ;
	virtual long __cdecl clearButtonMode() = 0 ;
	virtual Iosapi::Foundation::NSRect __cdecl clearButtonRectForBounds(Iosapi::Foundation::NSRect bounds) = 0 ;
	virtual bool __cdecl clearsOnBeginEditing() = 0 ;
	virtual void * __cdecl delegate() = 0 ;
	virtual _di_UIImage __cdecl disabledBackground() = 0 ;
	virtual void __cdecl drawPlaceholderInRect(Iosapi::Foundation::NSRect rect) = 0 ;
	virtual void __cdecl drawTextInRect(Iosapi::Foundation::NSRect rect) = 0 ;
	virtual Iosapi::Foundation::NSRect __cdecl editingRectForBounds(Iosapi::Foundation::NSRect bounds) = 0 ;
	virtual _di_UIFont __cdecl font() = 0 ;
	HIDESBASE virtual _di_UIView __cdecl inputAccessoryView() = 0 ;
	HIDESBASE virtual _di_UIView __cdecl inputView() = 0 ;
	virtual bool __cdecl isEditing() = 0 ;
	virtual _di_UIView __cdecl leftView() = 0 ;
	virtual long __cdecl leftViewMode() = 0 ;
	virtual Iosapi::Foundation::NSRect __cdecl leftViewRectForBounds(Iosapi::Foundation::NSRect bounds) = 0 ;
	virtual double __cdecl minimumFontSize() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl placeholder() = 0 ;
	virtual Iosapi::Foundation::NSRect __cdecl placeholderRectForBounds(Iosapi::Foundation::NSRect bounds) = 0 ;
	virtual _di_UIView __cdecl rightView() = 0 ;
	virtual long __cdecl rightViewMode() = 0 ;
	virtual Iosapi::Foundation::NSRect __cdecl rightViewRectForBounds(Iosapi::Foundation::NSRect bounds) = 0 ;
	virtual _di_UITextRange __cdecl selectedTextRange() = 0 ;
	virtual void __cdecl setAdjustsFontSizeToFitWidth(bool adjustsFontSizeToFitWidth) = 0 ;
	virtual void __cdecl setBackground(_di_UIImage background) = 0 ;
	virtual void __cdecl setBorderStyle(long borderStyle) = 0 ;
	virtual void __cdecl setClearButtonMode(long clearButtonMode) = 0 ;
	virtual void __cdecl setClearsOnBeginEditing(bool clearsOnBeginEditing) = 0 ;
	virtual void __cdecl setDelegate(void * delegate) = 0 ;
	virtual void __cdecl setDisabledBackground(_di_UIImage disabledBackground) = 0 ;
	virtual void __cdecl setFont(_di_UIFont font) = 0 ;
	virtual void __cdecl setInputAccessoryView(_di_UIView inputAccessoryView) = 0 ;
	virtual void __cdecl setInputView(_di_UIView inputView) = 0 ;
	virtual void __cdecl setLeftView(_di_UIView leftView) = 0 ;
	virtual void __cdecl setLeftViewMode(long leftViewMode) = 0 ;
	virtual void __cdecl setMinimumFontSize(double minimumFontSize) = 0 ;
	virtual void __cdecl setPlaceholder(Iosapi::Foundation::_di_NSString placeholder) = 0 ;
	virtual void __cdecl setRightView(_di_UIView rightView) = 0 ;
	virtual void __cdecl setRightViewMode(long rightViewMode) = 0 ;
	virtual void __cdecl setText(Iosapi::Foundation::_di_NSString text) = 0 ;
	virtual void __cdecl setTextAlignment(long textAlignment) = 0 ;
	virtual void __cdecl setTextColor(_di_UIColor textColor) = 0 ;
	virtual void __cdecl setTintAdjustmentMode(long mode) = 0 ;
	virtual void __cdecl setAttributedText(Iosapi::Foundation::_di_NSAttributedString attributedText) = 0 ;
	virtual void * __cdecl text() = 0 ;
	virtual long __cdecl textAlignment() = 0 ;
	virtual _di_UIColor __cdecl textColor() = 0 ;
	virtual Iosapi::Foundation::NSRect __cdecl textRectForBounds(Iosapi::Foundation::NSRect bounds) = 0 ;
	virtual Iosapi::Foundation::_di_NSAttributedString __cdecl attributedText() = 0 ;
	virtual long __cdecl autocapitalizationType() = 0 ;
	virtual long __cdecl autocorrectionType() = 0 ;
	virtual bool __cdecl enablesReturnKeyAutomatically() = 0 ;
	virtual bool __cdecl isSecureTextEntry() = 0 ;
	virtual long __cdecl keyboardAppearance() = 0 ;
	virtual long __cdecl keyboardType() = 0 ;
	virtual long __cdecl returnKeyType() = 0 ;
	virtual void __cdecl setAutocapitalizationType(long autocapitalizationType) = 0 ;
	virtual void __cdecl setAutocorrectionType(long autocorrectionType) = 0 ;
	virtual void __cdecl setEnablesReturnKeyAutomatically(bool enablesReturnKeyAutomatically) = 0 ;
	virtual void __cdecl setKeyboardAppearance(long keyboardAppearance) = 0 ;
	virtual void __cdecl setKeyboardType(long keyboardType) = 0 ;
	virtual void __cdecl setReturnKeyType(long returnKeyType) = 0 ;
	virtual void __cdecl setSecureTextEntry(bool secureTextEntry) = 0 ;
	virtual void __cdecl setSpellCheckingType(int spellCheckingType) = 0 ;
	virtual int __cdecl spellCheckingType() = 0 ;
	virtual void __cdecl setSelectedTextRange(_di_UITextRange SelectedTextRange) = 0 ;
	virtual void __cdecl unmarkText() = 0 ;
	virtual _di_UITextPosition __cdecl beginningOfDocument() = 0 ;
	virtual long __cdecl offsetFromPosition(_di_UITextPosition from, _di_UITextPosition toPosition) = 0 ;
	virtual _di_UITextPosition __cdecl endOfDocument() = 0 ;
	virtual _di_UITextPosition __cdecl positionFromPosition(_di_UITextPosition position, long offset) = 0 /* overload */;
	virtual _di_UITextRange __cdecl textRangeFromPosition(_di_UITextPosition fromPosition, _di_UITextPosition toPosition) = 0 ;
};

class PASCALIMPLEMENTATION TUITextField : public Macapi::Objectivec::TOCGenericImport__2<_di_UITextFieldClass,_di_UITextField>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UITextFieldClass,_di_UITextField> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUITextField(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UITextFieldClass,_di_UITextField>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUITextField() { }
	
};


__interface  INTERFACE_UUID("{B4D99C03-D8EE-4C48-BC7E-E235C5E5AA62}") UITableViewClass  : public UIScrollViewClass 
{
	
};

__interface  INTERFACE_UUID("{01DD1629-AB00-4191-979E-9DF263C4CA98}") UITableView  : public UIScrollView 
{
	HIDESBASE virtual void * __cdecl initWithFrame(Iosapi::Foundation::NSRect frame, long style) = 0 ;
	virtual long __cdecl style() = 0 ;
	virtual void __cdecl setDataSource(void * dataSource) = 0 ;
	virtual void * __cdecl dataSource() = 0 ;
	HIDESBASE virtual void __cdecl setDelegate(void * delegate) = 0 ;
	HIDESBASE virtual void * __cdecl delegate() = 0 ;
	virtual void __cdecl setRowHeight(double rowHeight) = 0 ;
	virtual double __cdecl rowHeight() = 0 ;
	virtual void __cdecl setSectionHeaderHeight(double sectionHeaderHeight) = 0 ;
	virtual double __cdecl sectionHeaderHeight() = 0 ;
	virtual void __cdecl setSectionFooterHeight(double sectionFooterHeight) = 0 ;
	virtual double __cdecl sectionFooterHeight() = 0 ;
	virtual void __cdecl setEstimatedRowHeight(double estimatedRowHeight) = 0 ;
	virtual double __cdecl estimatedRowHeight() = 0 ;
	virtual void __cdecl setEstimatedSectionHeaderHeight(double estimatedSectionHeaderHeight) = 0 ;
	virtual double __cdecl estimatedSectionHeaderHeight() = 0 ;
	virtual void __cdecl setEstimatedSectionFooterHeight(double estimatedSectionFooterHeight) = 0 ;
	virtual double __cdecl estimatedSectionFooterHeight() = 0 ;
	virtual void __cdecl setSeparatorInset(UIEdgeInsets separatorInset) = 0 ;
	virtual UIEdgeInsets __cdecl separatorInset() = 0 ;
	virtual void __cdecl setBackgroundView(_di_UIView backgroundView) = 0 ;
	virtual _di_UIView __cdecl backgroundView() = 0 ;
	virtual void __cdecl reloadData() = 0 ;
	virtual void __cdecl reloadSectionIndexTitles() = 0 ;
	virtual long __cdecl numberOfSections() = 0 ;
	virtual long __cdecl numberOfRowsInSection(long section) = 0 ;
	virtual Iosapi::Foundation::NSRect __cdecl rectForSection(long section) = 0 ;
	virtual Iosapi::Foundation::NSRect __cdecl rectForHeaderInSection(long section) = 0 ;
	virtual Iosapi::Foundation::NSRect __cdecl rectForFooterInSection(long section) = 0 ;
	virtual Iosapi::Foundation::NSRect __cdecl rectForRowAtIndexPath(Iosapi::Foundation::_di_NSIndexPath indexPath) = 0 ;
	virtual Iosapi::Foundation::_di_NSIndexPath __cdecl indexPathForRowAtPoint(Iosapi::Foundation::NSPoint point) = 0 ;
	virtual Iosapi::Foundation::_di_NSIndexPath __cdecl indexPathForCell(_di_UITableViewCell cell) = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl indexPathsForRowsInRect(Iosapi::Foundation::NSRect rect) = 0 ;
	virtual _di_UITableViewCell __cdecl cellForRowAtIndexPath(Iosapi::Foundation::_di_NSIndexPath indexPath) = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl visibleCells() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl indexPathsForVisibleRows() = 0 ;
	virtual _di_UITableViewHeaderFooterView __cdecl headerViewForSection(long section) = 0 ;
	virtual _di_UITableViewHeaderFooterView __cdecl footerViewForSection(long section) = 0 ;
	virtual void __cdecl scrollToRowAtIndexPath(Iosapi::Foundation::_di_NSIndexPath indexPath, long atScrollPosition, bool animated) = 0 ;
	virtual void __cdecl scrollToNearestSelectedRowAtScrollPosition(long scrollPosition, bool animated) = 0 ;
	virtual void __cdecl beginUpdates() = 0 ;
	virtual void __cdecl endUpdates() = 0 ;
	virtual void __cdecl insertSections(Iosapi::Foundation::_di_NSIndexSet sections, long withRowAnimation) = 0 ;
	virtual void __cdecl deleteSections(Iosapi::Foundation::_di_NSIndexSet sections, long withRowAnimation) = 0 ;
	virtual void __cdecl reloadSections(Iosapi::Foundation::_di_NSIndexSet sections, long withRowAnimation) = 0 ;
	virtual void __cdecl moveSection(long section, long toSection) = 0 ;
	virtual void __cdecl insertRowsAtIndexPaths(Iosapi::Foundation::_di_NSArray indexPaths, long withRowAnimation) = 0 ;
	virtual void __cdecl deleteRowsAtIndexPaths(Iosapi::Foundation::_di_NSArray indexPaths, long withRowAnimation) = 0 ;
	virtual void __cdecl reloadRowsAtIndexPaths(Iosapi::Foundation::_di_NSArray indexPaths, long withRowAnimation) = 0 ;
	virtual void __cdecl moveRowAtIndexPath(Iosapi::Foundation::_di_NSIndexPath indexPath, Iosapi::Foundation::_di_NSIndexPath toIndexPath) = 0 ;
	virtual void __cdecl setEditing(bool editing) = 0 ;
	virtual bool __cdecl isEditing() = 0 ;
	virtual void __cdecl setEditingAnimated(bool editing, bool animated) = 0 ;
	virtual void __cdecl setAllowsSelection(bool allowsSelection) = 0 ;
	virtual bool __cdecl allowsSelection() = 0 ;
	virtual void __cdecl setAllowsSelectionDuringEditing(bool allowsSelectionDuringEditing) = 0 ;
	virtual bool __cdecl allowsSelectionDuringEditing() = 0 ;
	virtual void __cdecl setAllowsMultipleSelection(bool allowsMultipleSelection) = 0 ;
	virtual bool __cdecl allowsMultipleSelection() = 0 ;
	virtual void __cdecl setAllowsMultipleSelectionDuringEditing(bool allowsMultipleSelectionDuringEditing) = 0 ;
	virtual bool __cdecl allowsMultipleSelectionDuringEditing() = 0 ;
	virtual Iosapi::Foundation::_di_NSIndexPath __cdecl indexPathForSelectedRow() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl indexPathsForSelectedRows() = 0 ;
	virtual void __cdecl selectRowAtIndexPath(Iosapi::Foundation::_di_NSIndexPath indexPath, bool animated, long scrollPosition) = 0 ;
	virtual void __cdecl deselectRowAtIndexPath(Iosapi::Foundation::_di_NSIndexPath indexPath, bool animated) = 0 ;
	virtual void __cdecl setSectionIndexMinimumDisplayRowCount(long sectionIndexMinimumDisplayRowCount) = 0 ;
	virtual long __cdecl sectionIndexMinimumDisplayRowCount() = 0 ;
	virtual void __cdecl setSectionIndexColor(_di_UIColor sectionIndexColor) = 0 ;
	virtual _di_UIColor __cdecl sectionIndexColor() = 0 ;
	virtual void __cdecl setSectionIndexBackgroundColor(_di_UIColor sectionIndexBackgroundColor) = 0 ;
	virtual _di_UIColor __cdecl sectionIndexBackgroundColor() = 0 ;
	virtual void __cdecl setSectionIndexTrackingBackgroundColor(_di_UIColor sectionIndexTrackingBackgroundColor) = 0 ;
	virtual _di_UIColor __cdecl sectionIndexTrackingBackgroundColor() = 0 ;
	virtual void __cdecl setSeparatorStyle(long separatorStyle) = 0 ;
	virtual long __cdecl separatorStyle() = 0 ;
	virtual void __cdecl setSeparatorColor(_di_UIColor separatorColor) = 0 ;
	virtual _di_UIColor __cdecl separatorColor() = 0 ;
	virtual void __cdecl setTableHeaderView(_di_UIView tableHeaderView) = 0 ;
	virtual _di_UIView __cdecl tableHeaderView() = 0 ;
	virtual void __cdecl setTableFooterView(_di_UIView tableFooterView) = 0 ;
	virtual _di_UIView __cdecl tableFooterView() = 0 ;
	virtual void * __cdecl dequeueReusableCellWithIdentifier(Iosapi::Foundation::_di_NSString identifier) = 0 ;
	virtual void * __cdecl dequeueReusableCellWithIdentifierForIndexPath(Iosapi::Foundation::_di_NSString identifier, Iosapi::Foundation::_di_NSIndexPath forIndexPath) = 0 ;
	virtual void * __cdecl dequeueReusableHeaderFooterViewWithIdentifier(Iosapi::Foundation::_di_NSString identifier) = 0 ;
	virtual void __cdecl registerNibForCellReuseIdentifier(_di_UINib nib, Iosapi::Foundation::_di_NSString forCellReuseIdentifier) = 0 ;
	virtual void __cdecl registerClassForCellReuseIdentifier(void * cellClass, Iosapi::Foundation::_di_NSString forCellReuseIdentifier) = 0 ;
	virtual void __cdecl registerNibForHeaderFooterViewReuseIdentifier(_di_UINib nib, Iosapi::Foundation::_di_NSString forHeaderFooterViewReuseIdentifier) = 0 ;
	virtual void __cdecl registerClassForHeaderFooterViewReuseIdentifier(void * aClass, Iosapi::Foundation::_di_NSString forHeaderFooterViewReuseIdentifier) = 0 ;
};

class PASCALIMPLEMENTATION TUITableView : public Macapi::Objectivec::TOCGenericImport__2<_di_UITableViewClass,_di_UITableView>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UITableViewClass,_di_UITableView> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUITableView(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UITableViewClass,_di_UITableView>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUITableView() { }
	
};


__interface  INTERFACE_UUID("{884E0248-81B6-4CEF-9CD4-DD9FC4349B1E}") UITableViewCellClass  : public UIViewClass 
{
	
};

__interface  INTERFACE_UUID("{95157E68-D744-4006-88DD-24048B5FCB28}") UITableViewCell  : public UIView 
{
	virtual void * __cdecl initWithStyle(long style, Iosapi::Foundation::_di_NSString reuseIdentifier) = 0 ;
	virtual _di_UIImageView __cdecl imageView() = 0 ;
	virtual _di_UILabel __cdecl textLabel() = 0 ;
	virtual _di_UILabel __cdecl detailTextLabel() = 0 ;
	virtual _di_UIView __cdecl contentView() = 0 ;
	virtual void __cdecl setBackgroundView(_di_UIView backgroundView) = 0 ;
	virtual _di_UIView __cdecl backgroundView() = 0 ;
	virtual void __cdecl setSelectedBackgroundView(_di_UIView selectedBackgroundView) = 0 ;
	virtual _di_UIView __cdecl selectedBackgroundView() = 0 ;
	virtual void __cdecl setMultipleSelectionBackgroundView(_di_UIView multipleSelectionBackgroundView) = 0 ;
	virtual _di_UIView __cdecl multipleSelectionBackgroundView() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl reuseIdentifier() = 0 ;
	virtual void __cdecl prepareForReuse() = 0 ;
	virtual void __cdecl setSelectionStyle(long selectionStyle) = 0 ;
	virtual long __cdecl selectionStyle() = 0 ;
	virtual void __cdecl setSelected(bool selected) = 0 ;
	virtual bool __cdecl isSelected() = 0 ;
	virtual void __cdecl setHighlighted(bool highlighted) = 0 ;
	virtual bool __cdecl isHighlighted() = 0 ;
	virtual void __cdecl setSelectedAnimated(bool selected, bool animated) = 0 ;
	virtual void __cdecl setHighlightedAnimated(bool highlighted, bool animated) = 0 ;
	virtual long __cdecl editingStyle() = 0 ;
	virtual void __cdecl setShowsReorderControl(bool showsReorderControl) = 0 ;
	virtual bool __cdecl showsReorderControl() = 0 ;
	virtual void __cdecl setShouldIndentWhileEditing(bool shouldIndentWhileEditing) = 0 ;
	virtual bool __cdecl shouldIndentWhileEditing() = 0 ;
	virtual void __cdecl setAccessoryType(long accessoryType) = 0 ;
	virtual long __cdecl accessoryType() = 0 ;
	virtual void __cdecl setAccessoryView(_di_UIView accessoryView) = 0 ;
	virtual _di_UIView __cdecl accessoryView() = 0 ;
	virtual void __cdecl setEditingAccessoryType(long editingAccessoryType) = 0 ;
	virtual long __cdecl editingAccessoryType() = 0 ;
	virtual void __cdecl setEditingAccessoryView(_di_UIView editingAccessoryView) = 0 ;
	virtual _di_UIView __cdecl editingAccessoryView() = 0 ;
	virtual void __cdecl setIndentationLevel(long indentationLevel) = 0 ;
	virtual long __cdecl indentationLevel() = 0 ;
	virtual void __cdecl setIndentationWidth(double indentationWidth) = 0 ;
	virtual double __cdecl indentationWidth() = 0 ;
	virtual void __cdecl setSeparatorInset(UIEdgeInsets separatorInset) = 0 ;
	virtual UIEdgeInsets __cdecl separatorInset() = 0 ;
	virtual void __cdecl setEditing(bool editing) = 0 ;
	virtual bool __cdecl isEditing() = 0 ;
	virtual void __cdecl setEditingAnimated(bool editing, bool animated) = 0 ;
	virtual bool __cdecl showingDeleteConfirmation() = 0 ;
	virtual void __cdecl willTransitionToState(unsigned long state) = 0 ;
	virtual void __cdecl didTransitionToState(unsigned long state) = 0 ;
	HIDESBASE virtual void * __cdecl initWithFrame(Iosapi::Foundation::NSRect frame, Iosapi::Foundation::_di_NSString reuseIdentifier) = 0 ;
	virtual void __cdecl setText(Iosapi::Foundation::_di_NSString text) = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl text() = 0 ;
	virtual void __cdecl setFont(_di_UIFont font) = 0 ;
	virtual _di_UIFont __cdecl font() = 0 ;
	virtual void __cdecl setTextAlignment(long textAlignment) = 0 ;
	virtual long __cdecl textAlignment() = 0 ;
	virtual void __cdecl setLineBreakMode(long lineBreakMode) = 0 ;
	virtual long __cdecl lineBreakMode() = 0 ;
	virtual void __cdecl setTextColor(_di_UIColor textColor) = 0 ;
	virtual _di_UIColor __cdecl textColor() = 0 ;
	virtual void __cdecl setSelectedTextColor(_di_UIColor selectedTextColor) = 0 ;
	virtual _di_UIColor __cdecl selectedTextColor() = 0 ;
	virtual void __cdecl setImage(_di_UIImage image) = 0 ;
	virtual _di_UIImage __cdecl image() = 0 ;
	virtual void __cdecl setSelectedImage(_di_UIImage selectedImage) = 0 ;
	virtual _di_UIImage __cdecl selectedImage() = 0 ;
	virtual void __cdecl setHidesAccessoryWhenEditing(bool hidesAccessoryWhenEditing) = 0 ;
	virtual bool __cdecl hidesAccessoryWhenEditing() = 0 ;
	virtual void __cdecl setTarget(void * target) = 0 ;
	virtual void * __cdecl target() = 0 ;
	virtual void __cdecl setEditAction(void * editAction) = 0 ;
	virtual void * __cdecl editAction() = 0 ;
	virtual void __cdecl setAccessoryAction(void * accessoryAction) = 0 ;
	virtual void * __cdecl accessoryAction() = 0 ;
};

class PASCALIMPLEMENTATION TUITableViewCell : public Macapi::Objectivec::TOCGenericImport__2<_di_UITableViewCellClass,_di_UITableViewCell>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UITableViewCellClass,_di_UITableViewCell> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUITableViewCell(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UITableViewCellClass,_di_UITableViewCell>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUITableViewCell() { }
	
};


__interface  INTERFACE_UUID("{EDBA7674-8A12-4A75-826A-28685A6F5014}") UITableViewHeaderFooterViewClass  : public UIViewClass 
{
	
};

__interface  INTERFACE_UUID("{C26C9122-8ED4-4EB5-A68A-808ACE61F612}") UITableViewHeaderFooterView  : public UIView 
{
	HIDESBASE virtual void __cdecl setTintColor(_di_UIColor tintColor) = 0 ;
	HIDESBASE virtual _di_UIColor __cdecl tintColor() = 0 ;
	virtual _di_UILabel __cdecl textLabel() = 0 ;
	virtual _di_UILabel __cdecl detailTextLabel() = 0 ;
	virtual _di_UIView __cdecl contentView() = 0 ;
	virtual void __cdecl setBackgroundView(_di_UIView backgroundView) = 0 ;
	virtual _di_UIView __cdecl backgroundView() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl reuseIdentifier() = 0 ;
	virtual void * __cdecl initWithReuseIdentifier(Iosapi::Foundation::_di_NSString reuseIdentifier) = 0 ;
	virtual void __cdecl prepareForReuse() = 0 ;
};

class PASCALIMPLEMENTATION TUITableViewHeaderFooterView : public Macapi::Objectivec::TOCGenericImport__2<_di_UITableViewHeaderFooterViewClass,_di_UITableViewHeaderFooterView>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UITableViewHeaderFooterViewClass,_di_UITableViewHeaderFooterView> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUITableViewHeaderFooterView(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UITableViewHeaderFooterViewClass,_di_UITableViewHeaderFooterView>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUITableViewHeaderFooterView() { }
	
};


__interface  INTERFACE_UUID("{5DF576DE-534C-46C1-8834-D8DE06EA085B}") UIRefreshControlClass  : public UIControlClass 
{
	
};

__interface  INTERFACE_UUID("{F6235A35-C3DE-41E2-B099-9C180CA3D243}") UIRefreshControl  : public UIControl 
{
	HIDESBASE virtual void * __cdecl init() = 0 ;
	virtual bool __cdecl isRefreshing() = 0 ;
	HIDESBASE virtual void __cdecl setTintColor(_di_UIColor tintColor) = 0 ;
	HIDESBASE virtual _di_UIColor __cdecl tintColor() = 0 ;
	virtual void __cdecl setAttributedTitle(Iosapi::Foundation::_di_NSAttributedString attributedTitle) = 0 ;
	virtual Iosapi::Foundation::_di_NSAttributedString __cdecl attributedTitle() = 0 ;
	virtual void __cdecl beginRefreshing() = 0 ;
	virtual void __cdecl endRefreshing() = 0 ;
};

class PASCALIMPLEMENTATION TUIRefreshControl : public Macapi::Objectivec::TOCGenericImport__2<_di_UIRefreshControlClass,_di_UIRefreshControl>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UIRefreshControlClass,_di_UIRefreshControl> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUIRefreshControl(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UIRefreshControlClass,_di_UIRefreshControl>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUIRefreshControl() { }
	
};


__interface  INTERFACE_UUID("{32347938-7927-4C6F-8687-47D76753B5E7}") NSValueClass  : public Iosapi::Quartzcore::NSObjectClass 
{
	virtual void * __cdecl valueWithCGPoint(Iosapi::Foundation::NSPoint point) = 0 ;
	virtual void * __cdecl valueWithCGRect(Iosapi::Foundation::NSRect rect) = 0 ;
	virtual void * __cdecl valueWithCGSize(Iosapi::Foundation::NSSize size) = 0 ;
	virtual void * __cdecl valueWithUIEdgeInsets(UIEdgeInsets insets) = 0 ;
	virtual void * __cdecl valueWithUIOffset(UIOffset insets) = 0 ;
};

__interface  INTERFACE_UUID("{0539B6F1-D277-4BCA-95B2-A283B46CB248}") NSValue  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::NSPoint __cdecl CGPointValue() = 0 ;
	virtual Iosapi::Foundation::NSRect __cdecl CGRectValue() = 0 ;
	virtual Iosapi::Foundation::NSSize __cdecl CGSizeValue() = 0 ;
	virtual Iosapi::Coregraphics::CGAffineTransform __cdecl CGAffineTransformValue() = 0 ;
	virtual UIEdgeInsets __cdecl UIEdgeInsetsValue() = 0 ;
	virtual UIOffset __cdecl UIOffsetValue() = 0 ;
};

class PASCALIMPLEMENTATION TNSValue : public Macapi::Objectivec::TOCGenericImport__2<_di_NSValueClass,_di_NSValue>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSValueClass,_di_NSValue> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSValue(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSValueClass,_di_NSValue>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSValue() { }
	
};


__interface  INTERFACE_UUID("{F7091D12-BC73-4DC1-BDEE-0E543D088166}") UITextPositionClass  : public Iosapi::Quartzcore::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{D3C0C93C-6471-4068-B58F-24CDFFD71DFB}") UITextPosition  : public Iosapi::Foundation::NSObject 
{
	
};

class PASCALIMPLEMENTATION TUITextPosition : public Macapi::Objectivec::TOCGenericImport__2<_di_UITextPositionClass,_di_UITextPosition>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UITextPositionClass,_di_UITextPosition> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUITextPosition(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UITextPositionClass,_di_UITextPosition>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUITextPosition() { }
	
};


__interface  INTERFACE_UUID("{99904725-C91C-4DAD-A5C7-90362CDCA20C}") UITextSelectionRectClass  : public Iosapi::Quartzcore::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{531423A4-3DD8-4942-B989-ED6E2D4D0C52}") UITextSelectionRect  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::NSRect __cdecl rect() = 0 ;
	virtual long __cdecl writingDirection() = 0 ;
	virtual bool __cdecl containsStart() = 0 ;
	virtual bool __cdecl containsEnd() = 0 ;
	virtual bool __cdecl isVertical() = 0 ;
};

class PASCALIMPLEMENTATION TUITextSelectionRect : public Macapi::Objectivec::TOCGenericImport__2<_di_UITextSelectionRectClass,_di_UITextSelectionRect>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UITextSelectionRectClass,_di_UITextSelectionRect> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUITextSelectionRect(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UITextSelectionRectClass,_di_UITextSelectionRect>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUITextSelectionRect() { }
	
};


__interface  INTERFACE_UUID("{3BC960E3-2108-4B5E-8DF3-204CC427BF64}") UIDictationPhraseClass  : public Iosapi::Quartzcore::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{0F882345-0CA2-4722-B703-4B452A6A41BB}") UIDictationPhrase  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::_di_NSString __cdecl text() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl alternativeInterpretations() = 0 ;
};

class PASCALIMPLEMENTATION TUIDictationPhrase : public Macapi::Objectivec::TOCGenericImport__2<_di_UIDictationPhraseClass,_di_UIDictationPhrase>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UIDictationPhraseClass,_di_UIDictationPhrase> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUIDictationPhrase(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UIDictationPhraseClass,_di_UIDictationPhrase>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUIDictationPhrase() { }
	
};


__interface  INTERFACE_UUID("{FDC3C541-1D0D-4BA3-BCBC-16AA1F21954B}") UIActivityClass  : public Iosapi::Quartzcore::NSObjectClass 
{
	virtual long __cdecl activityCategory() = 0 ;
};

__interface  INTERFACE_UUID("{C3AEA2FC-F280-477C-AE17-A51E2980CAD2}") UIActivity  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::_di_NSString __cdecl activityType() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl activityTitle() = 0 ;
	virtual _di_UIImage __cdecl activityImage() = 0 ;
	virtual bool __cdecl canPerformWithActivityItems(Iosapi::Foundation::_di_NSArray activityItems) = 0 ;
	virtual void __cdecl prepareWithActivityItems(Iosapi::Foundation::_di_NSArray activityItems) = 0 ;
	virtual _di_UIViewController __cdecl activityViewController() = 0 ;
	virtual void __cdecl performActivity() = 0 ;
	virtual void __cdecl activityDidFinish(bool completed) = 0 ;
};

class PASCALIMPLEMENTATION TUIActivity : public Macapi::Objectivec::TOCGenericImport__2<_di_UIActivityClass,_di_UIActivity>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UIActivityClass,_di_UIActivity> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUIActivity(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UIActivityClass,_di_UIActivity>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUIActivity() { }
	
};


__interface  INTERFACE_UUID("{6ED5AF5B-44D7-443B-9698-B01A977C6E73}") UIActivityItemProviderClass  : public Iosapi::Foundation::NSOperationClass 
{
	
};

__interface  INTERFACE_UUID("{1C50384B-723C-4F7D-A647-C699CAC6660C}") UIActivityItemProvider  : public Iosapi::Foundation::NSOperation 
{
	virtual void * __cdecl initWithPlaceholderItem(void * placeholderItem) = 0 ;
	virtual void * __cdecl placeholderItem() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl activityType() = 0 ;
	virtual void * __cdecl item() = 0 ;
};

class PASCALIMPLEMENTATION TUIActivityItemProvider : public Macapi::Objectivec::TOCGenericImport__2<_di_UIActivityItemProviderClass,_di_UIActivityItemProvider>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UIActivityItemProviderClass,_di_UIActivityItemProvider> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUIActivityItemProvider(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UIActivityItemProviderClass,_di_UIActivityItemProvider>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUIActivityItemProvider() { }
	
};


__interface  INTERFACE_UUID("{DF2A9066-4CF0-4D2B-8621-34EAF2C91DAF}") UIAttachmentBehaviorClass  : public UIDynamicBehaviorClass 
{
	
};

__interface  INTERFACE_UUID("{ADC09523-5788-447F-BF8E-9BE0BACB9EA8}") UIAttachmentBehavior  : public UIDynamicBehavior 
{
	virtual void * __cdecl initWithItemAttachedToAnchor(void * item, Iosapi::Foundation::NSPoint attachedToAnchor) = 0 ;
	virtual void * __cdecl initWithItemOffsetFromCenterAttachedToAnchor(void * item, UIOffset offsetFromCenter, Iosapi::Foundation::NSPoint attachedToAnchor) = 0 ;
	virtual void * __cdecl initWithItemAttachedToItem(void * item1, void * attachedToItem) = 0 ;
	virtual void * __cdecl initWithItemOffsetFromCenterAttachedToItemOffsetFromCenter(void * item1, UIOffset offsetFromCenter, void * attachedToItem, UIOffset offsetFromCenter1) = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl items() = 0 ;
	virtual long __cdecl attachedBehaviorType() = 0 ;
	virtual void __cdecl setAnchorPoint(Iosapi::Foundation::NSPoint anchorPoint) = 0 ;
	virtual Iosapi::Foundation::NSPoint __cdecl anchorPoint() = 0 ;
	virtual void __cdecl setLength(double length) = 0 ;
	virtual double __cdecl length() = 0 ;
	virtual void __cdecl setDamping(double damping) = 0 ;
	virtual double __cdecl damping() = 0 ;
	virtual void __cdecl setFrequency(double frequency) = 0 ;
	virtual double __cdecl frequency() = 0 ;
};

class PASCALIMPLEMENTATION TUIAttachmentBehavior : public Macapi::Objectivec::TOCGenericImport__2<_di_UIAttachmentBehaviorClass,_di_UIAttachmentBehavior>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UIAttachmentBehaviorClass,_di_UIAttachmentBehavior> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUIAttachmentBehavior(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UIAttachmentBehaviorClass,_di_UIAttachmentBehavior>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUIAttachmentBehavior() { }
	
};


__interface  INTERFACE_UUID("{3C193BBE-6114-4E44-93AD-614D114D542D}") UICollectionViewClass  : public UIScrollViewClass 
{
	
};

__interface  INTERFACE_UUID("{36A67554-5D83-4FE1-B42F-C8BBF3804D52}") UICollectionView  : public UIScrollView 
{
	HIDESBASE virtual void * __cdecl initWithFrame(Iosapi::Foundation::NSRect frame, _di_UICollectionViewLayout collectionViewLayout) = 0 ;
	virtual void __cdecl setCollectionViewLayout(_di_UICollectionViewLayout collectionViewLayout) = 0 ;
	virtual _di_UICollectionViewLayout __cdecl collectionViewLayout() = 0 ;
	HIDESBASE virtual void __cdecl setDelegate(void * delegate) = 0 ;
	HIDESBASE virtual void * __cdecl delegate() = 0 ;
	virtual void __cdecl setDataSource(void * dataSource) = 0 ;
	virtual void * __cdecl dataSource() = 0 ;
	virtual void __cdecl setBackgroundView(_di_UIView backgroundView) = 0 ;
	virtual _di_UIView __cdecl backgroundView() = 0 ;
	virtual void __cdecl registerClassForCellWithReuseIdentifier(void * cellClass, Iosapi::Foundation::_di_NSString forCellWithReuseIdentifier) = 0 ;
	virtual void __cdecl registerNibForCellWithReuseIdentifier(_di_UINib nib, Iosapi::Foundation::_di_NSString forCellWithReuseIdentifier) = 0 ;
	virtual void __cdecl registerClassForSupplementaryViewOfKindWithReuseIdentifier(void * viewClass, Iosapi::Foundation::_di_NSString forSupplementaryViewOfKind, Iosapi::Foundation::_di_NSString withReuseIdentifier) = 0 ;
	virtual void __cdecl registerNibForSupplementaryViewOfKindWithReuseIdentifier(_di_UINib nib, Iosapi::Foundation::_di_NSString forSupplementaryViewOfKind, Iosapi::Foundation::_di_NSString withReuseIdentifier) = 0 ;
	virtual void * __cdecl dequeueReusableCellWithReuseIdentifier(Iosapi::Foundation::_di_NSString identifier, Iosapi::Foundation::_di_NSIndexPath forIndexPath) = 0 ;
	virtual void * __cdecl dequeueReusableSupplementaryViewOfKind(Iosapi::Foundation::_di_NSString elementKind, Iosapi::Foundation::_di_NSString withReuseIdentifier, Iosapi::Foundation::_di_NSIndexPath forIndexPath) = 0 ;
	virtual void __cdecl setAllowsSelection(bool allowsSelection) = 0 ;
	virtual bool __cdecl allowsSelection() = 0 ;
	virtual void __cdecl setAllowsMultipleSelection(bool allowsMultipleSelection) = 0 ;
	virtual bool __cdecl allowsMultipleSelection() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl indexPathsForSelectedItems() = 0 ;
	virtual void __cdecl selectItemAtIndexPath(Iosapi::Foundation::_di_NSIndexPath indexPath, bool animated, unsigned long scrollPosition) = 0 ;
	virtual void __cdecl deselectItemAtIndexPath(Iosapi::Foundation::_di_NSIndexPath indexPath, bool animated) = 0 ;
	virtual void __cdecl reloadData() = 0 ;
	virtual void __cdecl setCollectionViewLayoutAnimated(_di_UICollectionViewLayout layout, bool animated) = 0 ;
	virtual void __cdecl setCollectionViewLayoutAnimatedCompletion(_di_UICollectionViewLayout layout, bool animated, TUIKitCompletion completion) = 0 ;
	virtual _di_UICollectionViewTransitionLayout __cdecl startInteractiveTransitionToCollectionViewLayout(_di_UICollectionViewLayout layout, UICollectionViewLayoutInteractiveTransitionCompletion completion) = 0 ;
	virtual void __cdecl finishInteractiveTransition() = 0 ;
	virtual void __cdecl cancelInteractiveTransition() = 0 ;
	virtual long __cdecl numberOfSections() = 0 ;
	virtual long __cdecl numberOfItemsInSection(long section) = 0 ;
	virtual _di_UICollectionViewLayoutAttributes __cdecl layoutAttributesForItemAtIndexPath(Iosapi::Foundation::_di_NSIndexPath indexPath) = 0 ;
	virtual _di_UICollectionViewLayoutAttributes __cdecl layoutAttributesForSupplementaryElementOfKind(Iosapi::Foundation::_di_NSString kind, Iosapi::Foundation::_di_NSIndexPath atIndexPath) = 0 ;
	virtual Iosapi::Foundation::_di_NSIndexPath __cdecl indexPathForItemAtPoint(Iosapi::Foundation::NSPoint point) = 0 ;
	virtual Iosapi::Foundation::_di_NSIndexPath __cdecl indexPathForCell(_di_UICollectionViewCell cell) = 0 ;
	virtual _di_UICollectionViewCell __cdecl cellForItemAtIndexPath(Iosapi::Foundation::_di_NSIndexPath indexPath) = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl visibleCells() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl indexPathsForVisibleItems() = 0 ;
	virtual void __cdecl scrollToItemAtIndexPath(Iosapi::Foundation::_di_NSIndexPath indexPath, unsigned long atScrollPosition, bool animated) = 0 ;
	virtual void __cdecl insertSections(Iosapi::Foundation::_di_NSIndexSet sections) = 0 ;
	virtual void __cdecl deleteSections(Iosapi::Foundation::_di_NSIndexSet sections) = 0 ;
	virtual void __cdecl reloadSections(Iosapi::Foundation::_di_NSIndexSet sections) = 0 ;
	virtual void __cdecl moveSection(long section, long toSection) = 0 ;
	virtual void __cdecl insertItemsAtIndexPaths(Iosapi::Foundation::_di_NSArray indexPaths) = 0 ;
	virtual void __cdecl deleteItemsAtIndexPaths(Iosapi::Foundation::_di_NSArray indexPaths) = 0 ;
	virtual void __cdecl reloadItemsAtIndexPaths(Iosapi::Foundation::_di_NSArray indexPaths) = 0 ;
	virtual void __cdecl moveItemAtIndexPath(Iosapi::Foundation::_di_NSIndexPath indexPath, Iosapi::Foundation::_di_NSIndexPath toIndexPath) = 0 ;
	virtual void __cdecl performBatchUpdates(TUIKitAction updates, TUIKitCompletion completion) = 0 ;
};

class PASCALIMPLEMENTATION TUICollectionView : public Macapi::Objectivec::TOCGenericImport__2<_di_UICollectionViewClass,_di_UICollectionView>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UICollectionViewClass,_di_UICollectionView> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUICollectionView(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UICollectionViewClass,_di_UICollectionView>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUICollectionView() { }
	
};


__interface  INTERFACE_UUID("{6560C0A0-9E91-4C0E-826F-D147E96866B3}") UICollectionReusableViewClass  : public UIViewClass 
{
	
};

__interface  INTERFACE_UUID("{1F928B5D-F241-4F01-B725-EE0F21E8E7EF}") UICollectionReusableView  : public UIView 
{
	virtual Iosapi::Foundation::_di_NSString __cdecl reuseIdentifier() = 0 ;
	virtual void __cdecl prepareForReuse() = 0 ;
	virtual void __cdecl applyLayoutAttributes(_di_UICollectionViewLayoutAttributes layoutAttributes) = 0 ;
	virtual void __cdecl willTransitionFromLayout(_di_UICollectionViewLayout oldLayout, _di_UICollectionViewLayout toLayout) = 0 ;
	virtual void __cdecl didTransitionFromLayout(_di_UICollectionViewLayout oldLayout, _di_UICollectionViewLayout toLayout) = 0 ;
};

class PASCALIMPLEMENTATION TUICollectionReusableView : public Macapi::Objectivec::TOCGenericImport__2<_di_UICollectionReusableViewClass,_di_UICollectionReusableView>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UICollectionReusableViewClass,_di_UICollectionReusableView> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUICollectionReusableView(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UICollectionReusableViewClass,_di_UICollectionReusableView>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUICollectionReusableView() { }
	
};


__interface  INTERFACE_UUID("{8D91C07D-AF1A-42F6-B25D-03BEFC1B3F87}") UICollectionViewCellClass  : public UICollectionReusableViewClass 
{
	
};

__interface  INTERFACE_UUID("{21708BF5-FDD9-4DEE-ABE1-971F753182F0}") UICollectionViewCell  : public UICollectionReusableView 
{
	virtual _di_UIView __cdecl contentView() = 0 ;
	virtual void __cdecl setSelected(bool selected) = 0 ;
	virtual bool __cdecl isSelected() = 0 ;
	virtual void __cdecl setHighlighted(bool highlighted) = 0 ;
	virtual bool __cdecl isHighlighted() = 0 ;
	virtual void __cdecl setBackgroundView(_di_UIView backgroundView) = 0 ;
	virtual _di_UIView __cdecl backgroundView() = 0 ;
	virtual void __cdecl setSelectedBackgroundView(_di_UIView selectedBackgroundView) = 0 ;
	virtual _di_UIView __cdecl selectedBackgroundView() = 0 ;
};

class PASCALIMPLEMENTATION TUICollectionViewCell : public Macapi::Objectivec::TOCGenericImport__2<_di_UICollectionViewCellClass,_di_UICollectionViewCell>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UICollectionViewCellClass,_di_UICollectionViewCell> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUICollectionViewCell(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UICollectionViewCellClass,_di_UICollectionViewCell>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUICollectionViewCell() { }
	
};


__interface  INTERFACE_UUID("{AA2146A8-68A0-4A6F-AFA3-B9D07D7C6ED0}") UICollectionViewLayoutClass  : public Iosapi::Quartzcore::NSObjectClass 
{
	virtual void * __cdecl layoutAttributesClass() = 0 ;
	virtual void * __cdecl invalidationContextClass() = 0 ;
};

__interface  INTERFACE_UUID("{F5FF0DB7-EC28-41B7-9513-9E9E612E46B9}") UICollectionViewLayout  : public Iosapi::Foundation::NSObject 
{
	virtual _di_UICollectionView __cdecl collectionView() = 0 ;
	virtual void __cdecl invalidateLayout() = 0 ;
	virtual void __cdecl invalidateLayoutWithContext(_di_UICollectionViewLayoutInvalidationContext context) = 0 ;
	virtual void __cdecl registerClass(void * viewClass, Iosapi::Foundation::_di_NSString forDecorationViewOfKind) = 0 ;
	virtual void __cdecl registerNib(_di_UINib nib, Iosapi::Foundation::_di_NSString forDecorationViewOfKind) = 0 ;
	virtual void __cdecl prepareLayout() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl layoutAttributesForElementsInRect(Iosapi::Foundation::NSRect rect) = 0 ;
	virtual _di_UICollectionViewLayoutAttributes __cdecl layoutAttributesForItemAtIndexPath(Iosapi::Foundation::_di_NSIndexPath indexPath) = 0 ;
	virtual _di_UICollectionViewLayoutAttributes __cdecl layoutAttributesForSupplementaryViewOfKind(Iosapi::Foundation::_di_NSString kind, Iosapi::Foundation::_di_NSIndexPath atIndexPath) = 0 ;
	virtual _di_UICollectionViewLayoutAttributes __cdecl layoutAttributesForDecorationViewOfKind(Iosapi::Foundation::_di_NSString decorationViewKind, Iosapi::Foundation::_di_NSIndexPath atIndexPath) = 0 ;
	virtual bool __cdecl shouldInvalidateLayoutForBoundsChange(Iosapi::Foundation::NSRect newBounds) = 0 ;
	virtual _di_UICollectionViewLayoutInvalidationContext __cdecl invalidationContextForBoundsChange(Iosapi::Foundation::NSRect newBounds) = 0 ;
	virtual Iosapi::Foundation::NSPoint __cdecl targetContentOffsetForProposedContentOffsetWithScrollingVelocity(Iosapi::Foundation::NSPoint proposedContentOffset, Iosapi::Foundation::NSPoint withScrollingVelocity) = 0 ;
	virtual Iosapi::Foundation::NSPoint __cdecl targetContentOffsetForProposedContentOffset(Iosapi::Foundation::NSPoint proposedContentOffset) = 0 ;
	virtual Iosapi::Foundation::NSSize __cdecl collectionViewContentSize() = 0 ;
	virtual void __cdecl prepareForCollectionViewUpdates(Iosapi::Foundation::_di_NSArray updateItems) = 0 ;
	virtual void __cdecl finalizeCollectionViewUpdates() = 0 ;
	virtual void __cdecl prepareForAnimatedBoundsChange(Iosapi::Foundation::NSRect oldBounds) = 0 ;
	virtual void __cdecl finalizeAnimatedBoundsChange() = 0 ;
	virtual void __cdecl prepareForTransitionToLayout(_di_UICollectionViewLayout newLayout) = 0 ;
	virtual void __cdecl prepareForTransitionFromLayout(_di_UICollectionViewLayout oldLayout) = 0 ;
	virtual void __cdecl finalizeLayoutTransition() = 0 ;
	virtual _di_UICollectionViewLayoutAttributes __cdecl initialLayoutAttributesForAppearingItemAtIndexPath(Iosapi::Foundation::_di_NSIndexPath itemIndexPath) = 0 ;
	virtual _di_UICollectionViewLayoutAttributes __cdecl finalLayoutAttributesForDisappearingItemAtIndexPath(Iosapi::Foundation::_di_NSIndexPath itemIndexPath) = 0 ;
	virtual _di_UICollectionViewLayoutAttributes __cdecl initialLayoutAttributesForAppearingSupplementaryElementOfKind(Iosapi::Foundation::_di_NSString elementKind, Iosapi::Foundation::_di_NSIndexPath atIndexPath) = 0 ;
	virtual _di_UICollectionViewLayoutAttributes __cdecl finalLayoutAttributesForDisappearingSupplementaryElementOfKind(Iosapi::Foundation::_di_NSString elementKind, Iosapi::Foundation::_di_NSIndexPath atIndexPath) = 0 ;
	virtual _di_UICollectionViewLayoutAttributes __cdecl initialLayoutAttributesForAppearingDecorationElementOfKind(Iosapi::Foundation::_di_NSString elementKind, Iosapi::Foundation::_di_NSIndexPath atIndexPath) = 0 ;
	virtual _di_UICollectionViewLayoutAttributes __cdecl finalLayoutAttributesForDisappearingDecorationElementOfKind(Iosapi::Foundation::_di_NSString elementKind, Iosapi::Foundation::_di_NSIndexPath atIndexPath) = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl indexPathsToDeleteForSupplementaryViewOfKind(Iosapi::Foundation::_di_NSString kind) = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl indexPathsToDeleteForDecorationViewOfKind(Iosapi::Foundation::_di_NSString kind) = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl indexPathsToInsertForSupplementaryViewOfKind(Iosapi::Foundation::_di_NSString kind) = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl indexPathsToInsertForDecorationViewOfKind(Iosapi::Foundation::_di_NSString kind) = 0 ;
};

class PASCALIMPLEMENTATION TUICollectionViewLayout : public Macapi::Objectivec::TOCGenericImport__2<_di_UICollectionViewLayoutClass,_di_UICollectionViewLayout>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UICollectionViewLayoutClass,_di_UICollectionViewLayout> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUICollectionViewLayout(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UICollectionViewLayoutClass,_di_UICollectionViewLayout>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUICollectionViewLayout() { }
	
};


__interface  INTERFACE_UUID("{D29A6391-955B-4D84-9707-F9DA681DAEB5}") UICollectionViewTransitionLayoutClass  : public UICollectionViewLayoutClass 
{
	
};

__interface  INTERFACE_UUID("{20261023-16DA-4504-B0A2-3EDF7B017109}") UICollectionViewTransitionLayout  : public UICollectionViewLayout 
{
	virtual void __cdecl setTransitionProgress(double transitionProgress) = 0 ;
	virtual double __cdecl transitionProgress() = 0 ;
	virtual _di_UICollectionViewLayout __cdecl currentLayout() = 0 ;
	virtual _di_UICollectionViewLayout __cdecl nextLayout() = 0 ;
	virtual void * __cdecl initWithCurrentLayout(_di_UICollectionViewLayout currentLayout, _di_UICollectionViewLayout nextLayout) = 0 ;
	virtual void __cdecl updateValue(double value, Iosapi::Foundation::_di_NSString forAnimatedKey) = 0 ;
	virtual double __cdecl valueForAnimatedKey(Iosapi::Foundation::_di_NSString key) = 0 ;
};

class PASCALIMPLEMENTATION TUICollectionViewTransitionLayout : public Macapi::Objectivec::TOCGenericImport__2<_di_UICollectionViewTransitionLayoutClass,_di_UICollectionViewTransitionLayout>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UICollectionViewTransitionLayoutClass,_di_UICollectionViewTransitionLayout> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUICollectionViewTransitionLayout(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UICollectionViewTransitionLayoutClass,_di_UICollectionViewTransitionLayout>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUICollectionViewTransitionLayout() { }
	
};


__interface  INTERFACE_UUID("{DC65B4CD-7FD6-47F6-9190-A0A634D0F826}") UICollectionViewLayoutAttributesClass  : public Iosapi::Quartzcore::NSObjectClass 
{
	virtual void * __cdecl layoutAttributesForCellWithIndexPath(Iosapi::Foundation::_di_NSIndexPath indexPath) = 0 ;
	virtual void * __cdecl layoutAttributesForSupplementaryViewOfKind(Iosapi::Foundation::_di_NSString elementKind, Iosapi::Foundation::_di_NSIndexPath withIndexPath) = 0 ;
	virtual void * __cdecl layoutAttributesForDecorationViewOfKind(Iosapi::Foundation::_di_NSString decorationViewKind, Iosapi::Foundation::_di_NSIndexPath withIndexPath) = 0 ;
};

__interface  INTERFACE_UUID("{791D4D25-8E2A-4E50-B37E-81CBE79BB0C7}") UICollectionViewLayoutAttributes  : public Iosapi::Foundation::NSObject 
{
	virtual void __cdecl setFrame(Iosapi::Foundation::NSRect frame) = 0 ;
	virtual Iosapi::Foundation::NSRect __cdecl frame() = 0 ;
	virtual void __cdecl setCenter(Iosapi::Foundation::NSPoint center) = 0 ;
	virtual Iosapi::Foundation::NSPoint __cdecl center() = 0 ;
	virtual void __cdecl setSize(Iosapi::Foundation::NSSize size) = 0 ;
	virtual Iosapi::Foundation::NSSize __cdecl size() = 0 ;
	virtual void __cdecl setTransform3D(Iosapi::Quartzcore::CATransform3D transform3D) = 0 ;
	virtual Iosapi::Quartzcore::CATransform3D __cdecl transform3D() = 0 ;
	virtual void __cdecl setBounds(Iosapi::Foundation::NSRect bounds) = 0 ;
	virtual Iosapi::Foundation::NSRect __cdecl bounds() = 0 ;
	virtual void __cdecl setTransform(Iosapi::Coregraphics::CGAffineTransform transform) = 0 ;
	virtual Iosapi::Coregraphics::CGAffineTransform __cdecl transform() = 0 ;
	virtual void __cdecl setAlpha(double alpha) = 0 ;
	virtual double __cdecl alpha() = 0 ;
	virtual void __cdecl setZIndex(long zIndex) = 0 ;
	virtual long __cdecl zIndex() = 0 ;
	virtual void __cdecl setHidden(bool hidden) = 0 ;
	virtual bool __cdecl isHidden() = 0 ;
	virtual void __cdecl setIndexPath(Iosapi::Foundation::_di_NSIndexPath indexPath) = 0 ;
	virtual Iosapi::Foundation::_di_NSIndexPath __cdecl indexPath() = 0 ;
	virtual unsigned long __cdecl representedElementCategory() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl representedElementKind() = 0 ;
};

class PASCALIMPLEMENTATION TUICollectionViewLayoutAttributes : public Macapi::Objectivec::TOCGenericImport__2<_di_UICollectionViewLayoutAttributesClass,_di_UICollectionViewLayoutAttributes>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UICollectionViewLayoutAttributesClass,_di_UICollectionViewLayoutAttributes> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUICollectionViewLayoutAttributes(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UICollectionViewLayoutAttributesClass,_di_UICollectionViewLayoutAttributes>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUICollectionViewLayoutAttributes() { }
	
};


__interface  INTERFACE_UUID("{6BF98FAD-3D6E-45CF-8238-659BD83E687D}") UICollectionViewControllerClass  : public UIViewControllerClass 
{
	
};

__interface  INTERFACE_UUID("{BFBD8D2A-F355-45C1-B9CB-B897426D77DE}") UICollectionViewController  : public UIViewController 
{
	virtual void * __cdecl initWithCollectionViewLayout(_di_UICollectionViewLayout layout) = 0 ;
	virtual void __cdecl setCollectionView(_di_UICollectionView collectionView) = 0 ;
	virtual _di_UICollectionView __cdecl collectionView() = 0 ;
	virtual void __cdecl setClearsSelectionOnViewWillAppear(bool clearsSelectionOnViewWillAppear) = 0 ;
	virtual bool __cdecl clearsSelectionOnViewWillAppear() = 0 ;
	virtual void __cdecl setUseLayoutToLayoutNavigationTransitions(bool useLayoutToLayoutNavigationTransitions) = 0 ;
	virtual bool __cdecl useLayoutToLayoutNavigationTransitions() = 0 ;
	virtual _di_UICollectionViewLayout __cdecl collectionViewLayout() = 0 ;
};

class PASCALIMPLEMENTATION TUICollectionViewController : public Macapi::Objectivec::TOCGenericImport__2<_di_UICollectionViewControllerClass,_di_UICollectionViewController>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UICollectionViewControllerClass,_di_UICollectionViewController> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUICollectionViewController(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UICollectionViewControllerClass,_di_UICollectionViewController>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUICollectionViewController() { }
	
};


__interface  INTERFACE_UUID("{4CF76F00-8A20-4ABB-AD97-1621B8E62241}") UICollectionViewUpdateItemClass  : public Iosapi::Quartzcore::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{6F974B65-2051-4A4D-A28C-9CD534EF9D1B}") UICollectionViewUpdateItem  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::_di_NSIndexPath __cdecl indexPathBeforeUpdate() = 0 ;
	virtual Iosapi::Foundation::_di_NSIndexPath __cdecl indexPathAfterUpdate() = 0 ;
	virtual long __cdecl updateAction() = 0 ;
};

class PASCALIMPLEMENTATION TUICollectionViewUpdateItem : public Macapi::Objectivec::TOCGenericImport__2<_di_UICollectionViewUpdateItemClass,_di_UICollectionViewUpdateItem>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UICollectionViewUpdateItemClass,_di_UICollectionViewUpdateItem> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUICollectionViewUpdateItem(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UICollectionViewUpdateItemClass,_di_UICollectionViewUpdateItem>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUICollectionViewUpdateItem() { }
	
};


__interface  INTERFACE_UUID("{33F79B9B-346E-4E4A-AB21-39B716FBABAE}") UICollectionViewLayoutInvalidationContextClass  : public Iosapi::Quartzcore::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{911A1A76-6166-4345-8384-E971FD090830}") UICollectionViewLayoutInvalidationContext  : public Iosapi::Foundation::NSObject 
{
	virtual bool __cdecl invalidateEverything() = 0 ;
	virtual bool __cdecl invalidateDataSourceCounts() = 0 ;
};

class PASCALIMPLEMENTATION TUICollectionViewLayoutInvalidationContext : public Macapi::Objectivec::TOCGenericImport__2<_di_UICollectionViewLayoutInvalidationContextClass,_di_UICollectionViewLayoutInvalidationContext>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UICollectionViewLayoutInvalidationContextClass,_di_UICollectionViewLayoutInvalidationContext> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUICollectionViewLayoutInvalidationContext(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UICollectionViewLayoutInvalidationContextClass,_di_UICollectionViewLayoutInvalidationContext>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUICollectionViewLayoutInvalidationContext() { }
	
};


__interface  INTERFACE_UUID("{46B10E09-7799-4781-AB3A-63A58CD77946}") UICollectionViewFlowLayoutInvalidationContextClass  : public UICollectionViewLayoutInvalidationContextClass 
{
	
};

__interface  INTERFACE_UUID("{4264E9D9-9003-4D38-A8A0-67BB407894FC}") UICollectionViewFlowLayoutInvalidationContext  : public UICollectionViewLayoutInvalidationContext 
{
	virtual void __cdecl setInvalidateFlowLayoutDelegateMetrics(bool invalidateFlowLayoutDelegateMetrics) = 0 ;
	virtual bool __cdecl invalidateFlowLayoutDelegateMetrics() = 0 ;
	virtual void __cdecl setInvalidateFlowLayoutAttributes(bool invalidateFlowLayoutAttributes) = 0 ;
	virtual bool __cdecl invalidateFlowLayoutAttributes() = 0 ;
};

class PASCALIMPLEMENTATION TUICollectionViewFlowLayoutInvalidationContext : public Macapi::Objectivec::TOCGenericImport__2<_di_UICollectionViewFlowLayoutInvalidationContextClass,_di_UICollectionViewFlowLayoutInvalidationContext>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UICollectionViewFlowLayoutInvalidationContextClass,_di_UICollectionViewFlowLayoutInvalidationContext> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUICollectionViewFlowLayoutInvalidationContext(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UICollectionViewFlowLayoutInvalidationContextClass,_di_UICollectionViewFlowLayoutInvalidationContext>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUICollectionViewFlowLayoutInvalidationContext() { }
	
};


__interface  INTERFACE_UUID("{0117FC75-7F80-41F1-8B89-BD503F59026E}") UICollectionViewFlowLayoutClass  : public UICollectionViewLayoutClass 
{
	
};

__interface  INTERFACE_UUID("{E725AB6A-F9BF-43EB-B9B4-A9B5993AA09C}") UICollectionViewFlowLayout  : public UICollectionViewLayout 
{
	virtual void __cdecl setMinimumLineSpacing(double minimumLineSpacing) = 0 ;
	virtual double __cdecl minimumLineSpacing() = 0 ;
	virtual void __cdecl setMinimumInteritemSpacing(double minimumInteritemSpacing) = 0 ;
	virtual double __cdecl minimumInteritemSpacing() = 0 ;
	virtual void __cdecl setItemSize(Iosapi::Foundation::NSSize itemSize) = 0 ;
	virtual Iosapi::Foundation::NSSize __cdecl itemSize() = 0 ;
	virtual void __cdecl setScrollDirection(long scrollDirection) = 0 ;
	virtual long __cdecl scrollDirection() = 0 ;
	virtual void __cdecl setHeaderReferenceSize(Iosapi::Foundation::NSSize headerReferenceSize) = 0 ;
	virtual Iosapi::Foundation::NSSize __cdecl headerReferenceSize() = 0 ;
	virtual void __cdecl setFooterReferenceSize(Iosapi::Foundation::NSSize footerReferenceSize) = 0 ;
	virtual Iosapi::Foundation::NSSize __cdecl footerReferenceSize() = 0 ;
	virtual void __cdecl setSectionInset(UIEdgeInsets sectionInset) = 0 ;
	virtual UIEdgeInsets __cdecl sectionInset() = 0 ;
};

class PASCALIMPLEMENTATION TUICollectionViewFlowLayout : public Macapi::Objectivec::TOCGenericImport__2<_di_UICollectionViewFlowLayoutClass,_di_UICollectionViewFlowLayout>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UICollectionViewFlowLayoutClass,_di_UICollectionViewFlowLayout> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUICollectionViewFlowLayout(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UICollectionViewFlowLayoutClass,_di_UICollectionViewFlowLayout>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUICollectionViewFlowLayout() { }
	
};


__interface  INTERFACE_UUID("{75A747B5-2C29-44F2-8A4C-2D998D303E78}") UIInputViewClass  : public UIViewClass 
{
	
};

__interface  INTERFACE_UUID("{35329E54-29EF-4047-8260-FC667589BAC9}") UIInputView  : public UIView 
{
	virtual long __cdecl inputViewStyle() = 0 ;
	HIDESBASE virtual void * __cdecl initWithFrame(Iosapi::Foundation::NSRect frame, long inputViewStyle) = 0 ;
};

class PASCALIMPLEMENTATION TUIInputView : public Macapi::Objectivec::TOCGenericImport__2<_di_UIInputViewClass,_di_UIInputView>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UIInputViewClass,_di_UIInputView> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUIInputView(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UIInputViewClass,_di_UIInputView>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUIInputView() { }
	
};


__interface  INTERFACE_UUID("{7B62D662-4F69-4621-BB90-01717B09BDA3}") UIInterpolatingMotionEffectClass  : public UIMotionEffectClass 
{
	
};

__interface  INTERFACE_UUID("{B93069C3-334C-4E22-B1F2-61F0DC7BC8CC}") UIInterpolatingMotionEffect  : public UIMotionEffect 
{
	virtual void * __cdecl initWithKeyPath(Iosapi::Foundation::_di_NSString keyPath, long type) = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl keyPath() = 0 ;
	virtual long __cdecl type() = 0 ;
	virtual void __cdecl setMinimumRelativeValue(void * minimumRelativeValue) = 0 ;
	virtual void * __cdecl minimumRelativeValue() = 0 ;
	virtual void __cdecl setMaximumRelativeValue(void * maximumRelativeValue) = 0 ;
	virtual void * __cdecl maximumRelativeValue() = 0 ;
};

class PASCALIMPLEMENTATION TUIInterpolatingMotionEffect : public Macapi::Objectivec::TOCGenericImport__2<_di_UIInterpolatingMotionEffectClass,_di_UIInterpolatingMotionEffect>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UIInterpolatingMotionEffectClass,_di_UIInterpolatingMotionEffect> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUIInterpolatingMotionEffect(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UIInterpolatingMotionEffectClass,_di_UIInterpolatingMotionEffect>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUIInterpolatingMotionEffect() { }
	
};


__interface  INTERFACE_UUID("{B18F95E8-F774-4DC6-B0C6-F19245E870A0}") UIMotionEffectGroupClass  : public UIMotionEffectClass 
{
	
};

__interface  INTERFACE_UUID("{B8976777-FB31-41CC-B6B7-15150439F422}") UIMotionEffectGroup  : public UIMotionEffect 
{
	virtual void __cdecl setMotionEffects(Iosapi::Foundation::_di_NSArray motionEffects) = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl motionEffects() = 0 ;
};

class PASCALIMPLEMENTATION TUIMotionEffectGroup : public Macapi::Objectivec::TOCGenericImport__2<_di_UIMotionEffectGroupClass,_di_UIMotionEffectGroup>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UIMotionEffectGroupClass,_di_UIMotionEffectGroup> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUIMotionEffectGroup(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UIMotionEffectGroupClass,_di_UIMotionEffectGroup>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUIMotionEffectGroup() { }
	
};


__interface  INTERFACE_UUID("{C1D49297-E304-4D44-90A3-C326E7160A51}") UIScreenEdgePanGestureRecognizerClass  : public UIPanGestureRecognizerClass 
{
	
};

__interface  INTERFACE_UUID("{79935DE4-918F-495E-9D9A-4C1F6AF78148}") UIScreenEdgePanGestureRecognizer  : public UIPanGestureRecognizer 
{
	virtual void __cdecl setEdges(unsigned long edges) = 0 ;
	virtual unsigned long __cdecl edges() = 0 ;
};

class PASCALIMPLEMENTATION TUIScreenEdgePanGestureRecognizer : public Macapi::Objectivec::TOCGenericImport__2<_di_UIScreenEdgePanGestureRecognizerClass,_di_UIScreenEdgePanGestureRecognizer>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UIScreenEdgePanGestureRecognizerClass,_di_UIScreenEdgePanGestureRecognizer> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUIScreenEdgePanGestureRecognizer(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UIScreenEdgePanGestureRecognizerClass,_di_UIScreenEdgePanGestureRecognizer>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUIScreenEdgePanGestureRecognizer() { }
	
};


__interface  INTERFACE_UUID("{91087F13-8FE1-4366-AF81-7DA102BEA705}") UIPercentDrivenInteractiveTransitionClass  : public Iosapi::Quartzcore::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{351784D5-4446-408D-AF96-4DD15A60A860}") UIPercentDrivenInteractiveTransition  : public Iosapi::Foundation::NSObject 
{
	virtual double __cdecl duration() = 0 ;
	virtual double __cdecl percentComplete() = 0 ;
	virtual void __cdecl setCompletionSpeed(double completionSpeed) = 0 ;
	virtual double __cdecl completionSpeed() = 0 ;
	virtual void __cdecl setCompletionCurve(long completionCurve) = 0 ;
	virtual long __cdecl completionCurve() = 0 ;
	virtual void __cdecl updateInteractiveTransition(double percentComplete) = 0 ;
	virtual void __cdecl cancelInteractiveTransition() = 0 ;
	virtual void __cdecl finishInteractiveTransition() = 0 ;
};

class PASCALIMPLEMENTATION TUIPercentDrivenInteractiveTransition : public Macapi::Objectivec::TOCGenericImport__2<_di_UIPercentDrivenInteractiveTransitionClass,_di_UIPercentDrivenInteractiveTransition>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UIPercentDrivenInteractiveTransitionClass,_di_UIPercentDrivenInteractiveTransition> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUIPercentDrivenInteractiveTransition(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UIPercentDrivenInteractiveTransitionClass,_di_UIPercentDrivenInteractiveTransition>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUIPercentDrivenInteractiveTransition() { }
	
};


__interface  INTERFACE_UUID("{760B4ED2-5FE7-4A2C-BAE7-4292CE9814CA}") UIPushBehaviorClass  : public UIDynamicBehaviorClass 
{
	
};

__interface  INTERFACE_UUID("{5CA9B06C-A462-4C10-A6AA-1A486E2142AA}") UIPushBehavior  : public UIDynamicBehavior 
{
	virtual void * __cdecl initWithItems(Iosapi::Foundation::_di_NSArray items, long mode) = 0 ;
	virtual void __cdecl addItem(void * item) = 0 ;
	virtual void __cdecl removeItem(void * item) = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl items() = 0 ;
	virtual UIOffset __cdecl targetOffsetFromCenterForItem(void * item) = 0 ;
	virtual void __cdecl setTargetOffsetFromCenter(UIOffset o, void * forItem) = 0 ;
	virtual long __cdecl mode() = 0 ;
	virtual void __cdecl setActive(bool active) = 0 ;
	virtual bool __cdecl active() = 0 ;
	virtual void __cdecl setAngle(double angle) = 0 ;
	virtual double __cdecl angle() = 0 ;
	virtual void __cdecl setMagnitude(double magnitude) = 0 ;
	virtual double __cdecl magnitude() = 0 ;
	virtual void __cdecl setPushDirection(Iosapi::Coregraphics::CGVector pushDirection) = 0 ;
	virtual Iosapi::Coregraphics::CGVector __cdecl pushDirection() = 0 ;
	virtual void __cdecl setAngleMagnitude(double angle, double magnitude) = 0 ;
};

class PASCALIMPLEMENTATION TUIPushBehavior : public Macapi::Objectivec::TOCGenericImport__2<_di_UIPushBehaviorClass,_di_UIPushBehavior>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UIPushBehaviorClass,_di_UIPushBehavior> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUIPushBehavior(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UIPushBehaviorClass,_di_UIPushBehavior>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUIPushBehavior() { }
	
};


__interface  INTERFACE_UUID("{7F2461BC-6BAF-49CF-8730-A5C1BE12085E}") UISnapBehaviorClass  : public UIDynamicBehaviorClass 
{
	
};

__interface  INTERFACE_UUID("{D612BA28-20F8-4229-BFB0-5EA0AAEDC5A2}") UISnapBehavior  : public UIDynamicBehavior 
{
	virtual void * __cdecl initWithItem(void * item, Iosapi::Foundation::NSPoint snapToPoint) = 0 ;
	virtual void __cdecl setDamping(double damping) = 0 ;
	virtual double __cdecl damping() = 0 ;
};

class PASCALIMPLEMENTATION TUISnapBehavior : public Macapi::Objectivec::TOCGenericImport__2<_di_UISnapBehaviorClass,_di_UISnapBehavior>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UISnapBehaviorClass,_di_UISnapBehavior> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUISnapBehavior(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UISnapBehaviorClass,_di_UISnapBehavior>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUISnapBehavior() { }
	
};


__interface  INTERFACE_UUID("{BA78DD39-2BBD-4178-B2F2-45BFFAD1173E}") UIDynamicItemBehaviorClass  : public UIDynamicBehaviorClass 
{
	
};

__interface  INTERFACE_UUID("{3AE9A75B-C278-429E-84E5-A2FD54C9680A}") UIDynamicItemBehavior  : public UIDynamicBehavior 
{
	virtual void * __cdecl initWithItems(Iosapi::Foundation::_di_NSArray items) = 0 ;
	virtual void __cdecl addItem(void * item) = 0 ;
	virtual void __cdecl removeItem(void * item) = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl items() = 0 ;
	virtual void __cdecl setElasticity(double elasticity) = 0 ;
	virtual double __cdecl elasticity() = 0 ;
	virtual void __cdecl setFriction(double friction) = 0 ;
	virtual double __cdecl friction() = 0 ;
	virtual void __cdecl setDensity(double density) = 0 ;
	virtual double __cdecl density() = 0 ;
	virtual void __cdecl setResistance(double resistance) = 0 ;
	virtual double __cdecl resistance() = 0 ;
	virtual void __cdecl setAngularResistance(double angularResistance) = 0 ;
	virtual double __cdecl angularResistance() = 0 ;
	virtual void __cdecl setAllowsRotation(bool allowsRotation) = 0 ;
	virtual bool __cdecl allowsRotation() = 0 ;
	virtual void __cdecl addLinearVelocity(Iosapi::Foundation::NSPoint velocity, void * forItem) = 0 ;
	virtual Iosapi::Foundation::NSPoint __cdecl linearVelocityForItem(void * item) = 0 ;
	virtual void __cdecl addAngularVelocity(double velocity, void * forItem) = 0 ;
	virtual double __cdecl angularVelocityForItem(void * item) = 0 ;
};

class PASCALIMPLEMENTATION TUIDynamicItemBehavior : public Macapi::Objectivec::TOCGenericImport__2<_di_UIDynamicItemBehaviorClass,_di_UIDynamicItemBehavior>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UIDynamicItemBehaviorClass,_di_UIDynamicItemBehavior> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUIDynamicItemBehavior(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UIDynamicItemBehaviorClass,_di_UIDynamicItemBehavior>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUIDynamicItemBehavior() { }
	
};


__interface  INTERFACE_UUID("{8AA7EBC2-67CC-4F98-89F4-6F62B458E94E}") UIGravityBehaviorClass  : public UIDynamicBehaviorClass 
{
	
};

__interface  INTERFACE_UUID("{1C18CC48-BFEA-4839-86EB-1788606CA585}") UIGravityBehavior  : public UIDynamicBehavior 
{
	virtual void * __cdecl initWithItems(Iosapi::Foundation::_di_NSArray items) = 0 ;
	virtual void __cdecl addItem(void * item) = 0 ;
	virtual void __cdecl removeItem(void * item) = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl items() = 0 ;
	virtual void __cdecl setGravityDirection(Iosapi::Coregraphics::CGVector gravityDirection) = 0 ;
	virtual Iosapi::Coregraphics::CGVector __cdecl gravityDirection() = 0 ;
	virtual void __cdecl setAngle(double angle) = 0 ;
	virtual double __cdecl angle() = 0 ;
	virtual void __cdecl setMagnitude(double magnitude) = 0 ;
	virtual double __cdecl magnitude() = 0 ;
	virtual void __cdecl setAngleMagnitude(double angle, double magnitude) = 0 ;
};

class PASCALIMPLEMENTATION TUIGravityBehavior : public Macapi::Objectivec::TOCGenericImport__2<_di_UIGravityBehaviorClass,_di_UIGravityBehavior>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UIGravityBehaviorClass,_di_UIGravityBehavior> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUIGravityBehavior(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UIGravityBehaviorClass,_di_UIGravityBehavior>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUIGravityBehavior() { }
	
};


__interface  INTERFACE_UUID("{5C52525A-064C-4D86-8D09-40967C735044}") UICollisionBehaviorClass  : public UIDynamicBehaviorClass 
{
	
};

__interface  INTERFACE_UUID("{5BEFAC2E-D356-4301-AAF6-CC95AFC4FBC6}") UICollisionBehavior  : public UIDynamicBehavior 
{
	virtual void * __cdecl initWithItems(Iosapi::Foundation::_di_NSArray items) = 0 ;
	virtual void __cdecl addItem(void * item) = 0 ;
	virtual void __cdecl removeItem(void * item) = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl items() = 0 ;
	virtual void __cdecl setCollisionMode(unsigned long collisionMode) = 0 ;
	virtual unsigned long __cdecl collisionMode() = 0 ;
	virtual void __cdecl setTranslatesReferenceBoundsIntoBoundary(bool translatesReferenceBoundsIntoBoundary) = 0 ;
	virtual bool __cdecl translatesReferenceBoundsIntoBoundary() = 0 ;
	virtual void __cdecl setTranslatesReferenceBoundsIntoBoundaryWithInsets(UIEdgeInsets insets) = 0 ;
	virtual void __cdecl addBoundaryWithIdentifierForPath(void * identifier, _di_UIBezierPath forPath) = 0 ;
	virtual void __cdecl addBoundaryWithIdentifierFromPointToPoint(void * identifier, Iosapi::Foundation::NSPoint fromPoint, Iosapi::Foundation::NSPoint toPoint) = 0 ;
	virtual _di_UIBezierPath __cdecl boundaryWithIdentifier(void * identifier) = 0 ;
	virtual void __cdecl removeBoundaryWithIdentifier(void * identifier) = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl boundaryIdentifiers() = 0 ;
	virtual void __cdecl removeAllBoundaries() = 0 ;
	virtual void __cdecl setCollisionDelegate(void * collisionDelegate) = 0 ;
	virtual void * __cdecl collisionDelegate() = 0 ;
};

class PASCALIMPLEMENTATION TUICollisionBehavior : public Macapi::Objectivec::TOCGenericImport__2<_di_UICollisionBehaviorClass,_di_UICollisionBehavior>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UICollisionBehaviorClass,_di_UICollisionBehavior> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUICollisionBehavior(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UICollisionBehaviorClass,_di_UICollisionBehavior>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUICollisionBehavior() { }
	
};


__interface  INTERFACE_UUID("{2A1B5C8A-57CE-4423-A857-6BD6BCC61F77}") UILayoutSupport  : public Macapi::Objectivec::IObjectiveC 
{
	virtual double __cdecl length() = 0 ;
};

__interface  INTERFACE_UUID("{864FE62C-7E23-4FC1-B075-9224C6E2E7E7}") NSTextStorageDelegate  : public Macapi::Objectivec::IObjectiveC 
{
	virtual void __cdecl textStorageWillProcessEditingRangeChangeInLength(_di_NSTextStorage textStorage, unsigned long willProcessEditing, Iosapi::Foundation::NSRange range, long changeInLength) = 0 ;
	virtual void __cdecl textStorageDidProcessEditingRangeChangeInLength(_di_NSTextStorage textStorage, unsigned long didProcessEditing, Iosapi::Foundation::NSRange range, long changeInLength) = 0 ;
};

__interface  INTERFACE_UUID("{BD66C85B-AB03-4AD7-8EF7-D86D1239A78F}") NSLayoutManagerDelegate  : public Macapi::Objectivec::IObjectiveC 
{
	virtual unsigned long __cdecl layoutManagerShouldGenerateGlyphsPropertiesCharacterIndexesFontForGlyphRange(_di_NSLayoutManager layoutManager, System::Word shouldGenerateGlyphs, long properties, unsigned long characterIndexes, _di_UIFont font, Iosapi::Foundation::NSRange forGlyphRange) = 0 ;
	virtual double __cdecl layoutManagerLineSpacingAfterGlyphAtIndexWithProposedLineFragmentRect(_di_NSLayoutManager layoutManager, unsigned long lineSpacingAfterGlyphAtIndex, Iosapi::Foundation::NSRect withProposedLineFragmentRect) = 0 ;
	virtual double __cdecl layoutManagerParagraphSpacingBeforeGlyphAtIndexWithProposedLineFragmentRect(_di_NSLayoutManager layoutManager, unsigned long paragraphSpacingBeforeGlyphAtIndex, Iosapi::Foundation::NSRect withProposedLineFragmentRect) = 0 ;
	virtual double __cdecl layoutManagerParagraphSpacingAfterGlyphAtIndexWithProposedLineFragmentRect(_di_NSLayoutManager layoutManager, unsigned long paragraphSpacingAfterGlyphAtIndex, Iosapi::Foundation::NSRect withProposedLineFragmentRect) = 0 ;
	virtual long __cdecl layoutManagerShouldUseActionForControlCharacterAtIndex(_di_NSLayoutManager layoutManager, long shouldUseAction, unsigned long forControlCharacterAtIndex) = 0 ;
	virtual bool __cdecl layoutManagerShouldBreakLineByWordBeforeCharacterAtIndex(_di_NSLayoutManager layoutManager, unsigned long shouldBreakLineByWordBeforeCharacterAtIndex) = 0 ;
	virtual bool __cdecl layoutManagerShouldBreakLineByHyphenatingBeforeCharacterAtIndex(_di_NSLayoutManager layoutManager, unsigned long shouldBreakLineByHyphenatingBeforeCharacterAtIndex) = 0 ;
	virtual Iosapi::Foundation::NSRect __cdecl layoutManagerBoundingBoxForControlGlyphAtIndexForTextContainerProposedLineFragmentGlyphPositionCharacterIndex(_di_NSLayoutManager layoutManager, unsigned long boundingBoxForControlGlyphAtIndex, _di_NSTextContainer forTextContainer, Iosapi::Foundation::NSRect proposedLineFragment, Iosapi::Foundation::NSPoint glyphPosition, unsigned long characterIndex) = 0 ;
	virtual void __cdecl layoutManagerDidInvalidateLayout(_di_NSLayoutManager sender) = 0 ;
	virtual void __cdecl layoutManagerDidCompleteLayoutForTextContainerAtEnd(_di_NSLayoutManager layoutManager, _di_NSTextContainer didCompleteLayoutForTextContainer, bool atEnd) = 0 ;
	virtual void __cdecl layoutManagerTextContainerDidChangeGeometryFromSize(_di_NSLayoutManager layoutManager, _di_NSTextContainer textContainer, Iosapi::Foundation::NSSize didChangeGeometryFromSize) = 0 ;
};

__interface  INTERFACE_UUID("{CFED2F72-F80E-4179-BCD8-89F174AD2A6C}") NSTextLayoutOrientationProvider  : public Macapi::Objectivec::IObjectiveC 
{
	virtual void __cdecl setLayoutOrientation(long layoutOrientation) = 0 ;
	virtual long __cdecl layoutOrientation() = 0 ;
};

__interface  INTERFACE_UUID("{4985C1EA-7959-4B50-BFE6-6CFBBD4C79B4}") NSTextAttachmentContainer  : public Macapi::Objectivec::IObjectiveC 
{
	virtual _di_UIImage __cdecl imageForBounds(Iosapi::Foundation::NSRect imageBounds, _di_NSTextContainer textContainer, unsigned long characterIndex) = 0 ;
	virtual Iosapi::Foundation::NSRect __cdecl attachmentBoundsForTextContainer(_di_NSTextContainer textContainer, Iosapi::Foundation::NSRect proposedLineFragment, Iosapi::Foundation::NSPoint glyphPosition, unsigned long characterIndex) = 0 ;
};

__interface  INTERFACE_UUID("{2ECAD696-6C20-4E0E-BC80-5E75345636BF}") UIAccelerometerDelegate  : public Macapi::Objectivec::IObjectiveC 
{
	virtual void __cdecl accelerometer(_di_UIAccelerometer accelerometer, _di_UIAcceleration didAccelerate) = 0 ;
};

__interface  INTERFACE_UUID("{5B5AAC30-C7BC-4033-9388-73640526A3E1}") UIAppearanceContainer  : public Macapi::Objectivec::IObjectiveC 
{
	
};

__interface  INTERFACE_UUID("{3CA77CF4-D712-4FBC-B517-3010BB559B11}") UIAppearance  : public Macapi::Objectivec::IObjectiveC 
{
	virtual void * __cdecl appearance() = 0 ;
	virtual void * __cdecl appearanceWhenContainedIn(void * ContainerClass) = 0 ;
};

__interface  INTERFACE_UUID("{5EF0F7FB-74A6-4BCF-9837-C2BB9FB7FF33}") UIDynamicItem  : public Macapi::Objectivec::IObjectiveC 
{
	virtual void __cdecl setCenter(Iosapi::Foundation::NSPoint center) = 0 ;
	virtual Iosapi::Foundation::NSPoint __cdecl center() = 0 ;
	virtual Iosapi::Foundation::NSRect __cdecl bounds() = 0 ;
	virtual void __cdecl setTransform(Iosapi::Coregraphics::CGAffineTransform transform) = 0 ;
	virtual Iosapi::Coregraphics::CGAffineTransform __cdecl transform() = 0 ;
};

__interface  INTERFACE_UUID("{2DA8B00F-F141-48BC-9AD0-3313E4958831}") UIScrollViewDelegate  : public Macapi::Objectivec::IObjectiveC 
{
	virtual void __cdecl scrollViewDidScroll(_di_UIScrollView scrollView) = 0 ;
	virtual void __cdecl scrollViewDidZoom(_di_UIScrollView scrollView) = 0 ;
	virtual void __cdecl scrollViewWillBeginDragging(_di_UIScrollView scrollView) = 0 ;
	virtual void __cdecl scrollViewWillEndDragging(_di_UIScrollView scrollView, Iosapi::Foundation::NSPoint withVelocity, void * targetContentOffset) = 0 ;
	virtual void __cdecl scrollViewDidEndDragging(_di_UIScrollView scrollView, bool willDecelerate) = 0 ;
	virtual void __cdecl scrollViewWillBeginDecelerating(_di_UIScrollView scrollView) = 0 ;
	virtual void __cdecl scrollViewDidEndDecelerating(_di_UIScrollView scrollView) = 0 ;
	virtual void __cdecl scrollViewDidEndScrollingAnimation(_di_UIScrollView scrollView) = 0 ;
	virtual _di_UIView __cdecl viewForZoomingInScrollView(_di_UIScrollView scrollView) = 0 ;
	virtual void __cdecl scrollViewWillBeginZooming(_di_UIScrollView scrollView, _di_UIView withView) = 0 ;
	virtual void __cdecl scrollViewDidEndZooming(_di_UIScrollView scrollView, _di_UIView withView, double atScale) = 0 ;
	virtual bool __cdecl scrollViewShouldScrollToTop(_di_UIScrollView scrollView) = 0 ;
	virtual void __cdecl scrollViewDidScrollToTop(_di_UIScrollView scrollView) = 0 ;
};

__interface  INTERFACE_UUID("{2464BC90-EB86-42B9-8747-9CCFE8F1AA98}") UITableViewDataSource  : public Macapi::Objectivec::IObjectiveC 
{
	virtual long __cdecl tableViewNumberOfRowsInSection(_di_UITableView tableView, long numberOfRowsInSection) = 0 ;
	virtual _di_UITableViewCell __cdecl tableViewCellForRowAtIndexPath(_di_UITableView tableView, Iosapi::Foundation::_di_NSIndexPath cellForRowAtIndexPath) = 0 ;
	virtual long __cdecl numberOfSectionsInTableView(_di_UITableView tableView) = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl tableViewTitleForHeaderInSection(_di_UITableView tableView, long titleForHeaderInSection) = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl tableViewTitleForFooterInSection(_di_UITableView tableView, long titleForFooterInSection) = 0 ;
	virtual bool __cdecl tableViewCanEditRowAtIndexPath(_di_UITableView tableView, Iosapi::Foundation::_di_NSIndexPath canEditRowAtIndexPath) = 0 ;
	virtual bool __cdecl tableViewCanMoveRowAtIndexPath(_di_UITableView tableView, Iosapi::Foundation::_di_NSIndexPath canMoveRowAtIndexPath) = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl sectionIndexTitlesForTableView(_di_UITableView tableView) = 0 ;
	virtual long __cdecl tableViewSectionForSectionIndexTitleAtIndex(_di_UITableView tableView, Iosapi::Foundation::_di_NSString sectionForSectionIndexTitle, long atIndex) = 0 ;
	virtual void __cdecl tableViewCommitEditingStyleForRowAtIndexPath(_di_UITableView tableView, long commitEditingStyle, Iosapi::Foundation::_di_NSIndexPath forRowAtIndexPath) = 0 ;
	virtual void __cdecl tableViewMoveRowAtIndexPathToIndexPath(_di_UITableView tableView, Iosapi::Foundation::_di_NSIndexPath moveRowAtIndexPath, Iosapi::Foundation::_di_NSIndexPath toIndexPath) = 0 ;
};

__interface  INTERFACE_UUID("{6F3B09F8-FD6E-4053-9F83-A52982090A41}") UITableViewDelegate  : public Macapi::Objectivec::IObjectiveC 
{
	virtual void __cdecl tableViewWillDisplayCellForRowAtIndexPath(_di_UITableView tableView, _di_UITableViewCell willDisplayCell, Iosapi::Foundation::_di_NSIndexPath forRowAtIndexPath) = 0 ;
	virtual void __cdecl tableViewWillDisplayHeaderViewForSection(_di_UITableView tableView, _di_UIView willDisplayHeaderView, long forSection) = 0 ;
	virtual void __cdecl tableViewWillDisplayFooterViewForSection(_di_UITableView tableView, _di_UIView willDisplayFooterView, long forSection) = 0 ;
	virtual void __cdecl tableViewDidEndDisplayingCellForRowAtIndexPath(_di_UITableView tableView, _di_UITableViewCell didEndDisplayingCell, Iosapi::Foundation::_di_NSIndexPath forRowAtIndexPath) = 0 ;
	virtual void __cdecl tableViewDidEndDisplayingHeaderViewForSection(_di_UITableView tableView, _di_UIView didEndDisplayingHeaderView, long forSection) = 0 ;
	virtual void __cdecl tableViewDidEndDisplayingFooterViewForSection(_di_UITableView tableView, _di_UIView didEndDisplayingFooterView, long forSection) = 0 ;
	virtual double __cdecl tableViewHeightForRowAtIndexPath(_di_UITableView tableView, Iosapi::Foundation::_di_NSIndexPath heightForRowAtIndexPath) = 0 ;
	virtual double __cdecl tableViewHeightForHeaderInSection(_di_UITableView tableView, long heightForHeaderInSection) = 0 ;
	virtual double __cdecl tableViewHeightForFooterInSection(_di_UITableView tableView, long heightForFooterInSection) = 0 ;
	virtual double __cdecl tableViewEstimatedHeightForRowAtIndexPath(_di_UITableView tableView, Iosapi::Foundation::_di_NSIndexPath estimatedHeightForRowAtIndexPath) = 0 ;
	virtual double __cdecl tableViewEstimatedHeightForHeaderInSection(_di_UITableView tableView, long estimatedHeightForHeaderInSection) = 0 ;
	virtual double __cdecl tableViewEstimatedHeightForFooterInSection(_di_UITableView tableView, long estimatedHeightForFooterInSection) = 0 ;
	virtual _di_UIView __cdecl tableViewViewForHeaderInSection(_di_UITableView tableView, long viewForHeaderInSection) = 0 ;
	virtual _di_UIView __cdecl tableViewViewForFooterInSection(_di_UITableView tableView, long viewForFooterInSection) = 0 ;
	virtual long __cdecl tableViewAccessoryTypeForRowWithIndexPath(_di_UITableView tableView, Iosapi::Foundation::_di_NSIndexPath accessoryTypeForRowWithIndexPath) = 0 ;
	virtual void __cdecl tableViewAccessoryButtonTappedForRowWithIndexPath(_di_UITableView tableView, Iosapi::Foundation::_di_NSIndexPath accessoryButtonTappedForRowWithIndexPath) = 0 ;
	virtual bool __cdecl tableViewShouldHighlightRowAtIndexPath(_di_UITableView tableView, Iosapi::Foundation::_di_NSIndexPath shouldHighlightRowAtIndexPath) = 0 ;
	virtual void __cdecl tableViewDidHighlightRowAtIndexPath(_di_UITableView tableView, Iosapi::Foundation::_di_NSIndexPath didHighlightRowAtIndexPath) = 0 ;
	virtual void __cdecl tableViewDidUnhighlightRowAtIndexPath(_di_UITableView tableView, Iosapi::Foundation::_di_NSIndexPath didUnhighlightRowAtIndexPath) = 0 ;
	virtual Iosapi::Foundation::_di_NSIndexPath __cdecl tableViewWillSelectRowAtIndexPath(_di_UITableView tableView, Iosapi::Foundation::_di_NSIndexPath willSelectRowAtIndexPath) = 0 ;
	virtual Iosapi::Foundation::_di_NSIndexPath __cdecl tableViewWillDeselectRowAtIndexPath(_di_UITableView tableView, Iosapi::Foundation::_di_NSIndexPath willDeselectRowAtIndexPath) = 0 ;
	virtual void __cdecl tableViewDidSelectRowAtIndexPath(_di_UITableView tableView, Iosapi::Foundation::_di_NSIndexPath didSelectRowAtIndexPath) = 0 ;
	virtual void __cdecl tableViewDidDeselectRowAtIndexPath(_di_UITableView tableView, Iosapi::Foundation::_di_NSIndexPath didDeselectRowAtIndexPath) = 0 ;
	virtual long __cdecl tableViewEditingStyleForRowAtIndexPath(_di_UITableView tableView, Iosapi::Foundation::_di_NSIndexPath editingStyleForRowAtIndexPath) = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl tableViewTitleForDeleteConfirmationButtonForRowAtIndexPath(_di_UITableView tableView, Iosapi::Foundation::_di_NSIndexPath titleForDeleteConfirmationButtonForRowAtIndexPath) = 0 ;
	virtual bool __cdecl tableViewShouldIndentWhileEditingRowAtIndexPath(_di_UITableView tableView, Iosapi::Foundation::_di_NSIndexPath shouldIndentWhileEditingRowAtIndexPath) = 0 ;
	virtual void __cdecl tableViewWillBeginEditingRowAtIndexPath(_di_UITableView tableView, Iosapi::Foundation::_di_NSIndexPath willBeginEditingRowAtIndexPath) = 0 ;
	virtual void __cdecl tableViewDidEndEditingRowAtIndexPath(_di_UITableView tableView, Iosapi::Foundation::_di_NSIndexPath didEndEditingRowAtIndexPath) = 0 ;
	virtual Iosapi::Foundation::_di_NSIndexPath __cdecl tableViewTargetIndexPathForMoveFromRowAtIndexPathToProposedIndexPath(_di_UITableView tableView, Iosapi::Foundation::_di_NSIndexPath targetIndexPathForMoveFromRowAtIndexPath, Iosapi::Foundation::_di_NSIndexPath toProposedIndexPath) = 0 ;
	virtual long __cdecl tableViewIndentationLevelForRowAtIndexPath(_di_UITableView tableView, Iosapi::Foundation::_di_NSIndexPath indentationLevelForRowAtIndexPath) = 0 ;
	virtual bool __cdecl tableViewShouldShowMenuForRowAtIndexPath(_di_UITableView tableView, Iosapi::Foundation::_di_NSIndexPath shouldShowMenuForRowAtIndexPath) = 0 ;
	virtual bool __cdecl tableViewCanPerformActionForRowAtIndexPathWithSender(_di_UITableView tableView, void * canPerformAction, Iosapi::Foundation::_di_NSIndexPath forRowAtIndexPath, void * withSender) = 0 ;
	virtual void __cdecl tableViewPerformActionForRowAtIndexPathWithSender(_di_UITableView tableView, void * performAction, Iosapi::Foundation::_di_NSIndexPath forRowAtIndexPath, void * withSender) = 0 ;
};

__interface  INTERFACE_UUID("{4F06B548-6BBD-4AAC-9B83-1156532069BA}") UIPickerViewAccessibilityDelegate  : public Macapi::Objectivec::IObjectiveC 
{
	virtual Iosapi::Foundation::_di_NSString __cdecl pickerViewAccessibilityLabelForComponent(_di_UIPickerView pickerView, long accessibilityLabelForComponent) = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl pickerViewAccessibilityHintForComponent(_di_UIPickerView pickerView, long accessibilityHintForComponent) = 0 ;
};

__interface  INTERFACE_UUID("{EEB6B631-889F-409C-B7EE-5AA432B8BC30}") UIScrollViewAccessibilityDelegate  : public Macapi::Objectivec::IObjectiveC 
{
	virtual Iosapi::Foundation::_di_NSString __cdecl accessibilityScrollStatusForScrollView(_di_UIScrollView scrollView) = 0 ;
};

__interface  INTERFACE_UUID("{0ABA3B1A-3A18-4B1F-A7C0-59FF25C9F098}") UIAccessibilityIdentification  : public Macapi::Objectivec::IObjectiveC 
{
	virtual void __cdecl setAccessibilityIdentifier(Iosapi::Foundation::_di_NSString accessibilityIdentifier) = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl accessibilityIdentifier() = 0 ;
};

__interface  INTERFACE_UUID("{1A216388-5C3C-4C46-A1ED-FD02D7674DDE}") UIGuidedAccessRestrictionDelegate  : public Macapi::Objectivec::IObjectiveC 
{
	virtual Iosapi::Foundation::_di_NSArray __cdecl guidedAccessRestrictionIdentifiers() = 0 ;
	virtual void __cdecl guidedAccessRestrictionWithIdentifier(Iosapi::Foundation::_di_NSString restrictionIdentifier, long didChangeState) = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl textForGuidedAccessRestrictionWithIdentifier(Iosapi::Foundation::_di_NSString restrictionIdentifier) = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl detailTextForGuidedAccessRestrictionWithIdentifier(Iosapi::Foundation::_di_NSString restrictionIdentifier) = 0 ;
};

__interface  INTERFACE_UUID("{79B2425F-02C8-4FBF-AB51-5188B117A058}") UIAccessibilityReadingContent  : public Macapi::Objectivec::IObjectiveC 
{
	virtual long __cdecl accessibilityLineNumberForPoint(Iosapi::Foundation::NSPoint point) = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl accessibilityContentForLineNumber(long lineNumber) = 0 ;
	virtual Iosapi::Foundation::NSRect __cdecl accessibilityFrameForLineNumber(long lineNumber) = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl accessibilityPageContent() = 0 ;
};

__interface  INTERFACE_UUID("{E7BE0DB1-72C2-4608-B2A5-74AD3130074C}") UITextInputTokenizer  : public Macapi::Objectivec::IObjectiveC 
{
	virtual _di_UITextRange __cdecl rangeEnclosingPosition(_di_UITextPosition position, long withGranularity, long inDirection) = 0 ;
	virtual bool __cdecl isPositionAtBoundaryInDirection(_di_UITextPosition position, long atBoundary, long inDirection) = 0 ;
	virtual _di_UITextPosition __cdecl positionFromPosition(_di_UITextPosition position, long toBoundary, long inDirection) = 0 ;
	virtual bool __cdecl isPositionWithinTextUnitInDirection(_di_UITextPosition position, long withinTextUnit, long inDirection) = 0 ;
};

__interface  INTERFACE_UUID("{8027D137-22AC-4095-8B59-4BD3F06B98D4}") UITextInputDelegate  : public Macapi::Objectivec::IObjectiveC 
{
	virtual void __cdecl selectionWillChange(void * textInput) = 0 ;
	virtual void __cdecl selectionDidChange(void * textInput) = 0 ;
	virtual void __cdecl textWillChange(void * textInput) = 0 ;
	virtual void __cdecl textDidChange(void * textInput) = 0 ;
};

__interface  INTERFACE_UUID("{DA87A484-146F-4A3D-84CA-09C1F3B86BD4}") UIActivityItemSource  : public Macapi::Objectivec::IObjectiveC 
{
	virtual void * __cdecl activityViewControllerPlaceholderItem(_di_UIActivityViewController activityViewController) = 0 ;
	virtual void * __cdecl activityViewControllerItemForActivityType(_di_UIActivityViewController activityViewController, Iosapi::Foundation::_di_NSString itemForActivityType) = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl activityViewControllerSubjectForActivityType(_di_UIActivityViewController activityViewController, Iosapi::Foundation::_di_NSString subjectForActivityType) = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl activityViewControllerDataTypeIdentifierForActivityType(_di_UIActivityViewController activityViewController, Iosapi::Foundation::_di_NSString dataTypeIdentifierForActivityType) = 0 ;
	virtual _di_UIImage __cdecl activityViewControllerThumbnailImageForActivityTypeSuggestedSize(_di_UIActivityViewController activityViewController, Iosapi::Foundation::_di_NSString thumbnailImageForActivityType, Iosapi::Foundation::NSSize suggestedSize) = 0 ;
};

__interface  INTERFACE_UUID("{15045B0D-B9E8-497D-961D-996C5D4ABC1D}") UIInputViewAudioFeedback  : public Macapi::Objectivec::IObjectiveC 
{
	virtual bool __cdecl enableInputClicksWhenVisible() = 0 ;
};

__interface  INTERFACE_UUID("{96419605-F83B-4F7A-ABEB-1F4F9368F00B}") UIStateRestoring  : public Macapi::Objectivec::IObjectiveC 
{
	virtual void * __cdecl restorationParent() = 0 ;
	virtual void * __cdecl objectRestorationClass() = 0 ;
	virtual void __cdecl encodeRestorableStateWithCoder(Iosapi::Foundation::_di_NSCoder coder) = 0 ;
	virtual void __cdecl decodeRestorableStateWithCoder(Iosapi::Foundation::_di_NSCoder coder) = 0 ;
	virtual void __cdecl applicationFinishedRestoringState() = 0 ;
};

__interface  INTERFACE_UUID("{7473D680-E494-4387-9F35-41C2B07A4FF1}") UIViewControllerRestoration  : public Macapi::Objectivec::IObjectiveC 
{
	virtual _di_UIViewController __cdecl viewControllerWithRestorationIdentifierPath(Iosapi::Foundation::_di_NSArray identifierComponents, Iosapi::Foundation::_di_NSCoder coder) = 0 ;
};

__interface  INTERFACE_UUID("{CEA7A538-0E78-40A0-9EF1-01B193BE4915}") UIDataSourceModelAssociation  : public Macapi::Objectivec::IObjectiveC 
{
	virtual Iosapi::Foundation::_di_NSString __cdecl modelIdentifierForElementAtIndexPath(Iosapi::Foundation::_di_NSIndexPath idx, _di_UIView inView) = 0 ;
	virtual Iosapi::Foundation::_di_NSIndexPath __cdecl indexPathForElementWithModelIdentifier(Iosapi::Foundation::_di_NSString identifier, _di_UIView inView) = 0 ;
};

__interface  INTERFACE_UUID("{8969FBAE-1327-480E-991C-FF04EBBA55E9}") UIObjectRestoration  : public Macapi::Objectivec::IObjectiveC 
{
	virtual void * __cdecl objectWithRestorationIdentifierPath(Iosapi::Foundation::_di_NSArray identifierComponents, Iosapi::Foundation::_di_NSCoder coder) = 0 ;
};

__interface  INTERFACE_UUID("{922C9E8B-4C1F-4789-A416-BA41BE33F90B}") UIViewControllerTransitioningDelegate  : public Macapi::Objectivec::IObjectiveC 
{
	virtual void * __cdecl animationControllerForPresentedController(_di_UIViewController presented, _di_UIViewController presentingController, _di_UIViewController sourceController) = 0 ;
	virtual void * __cdecl animationControllerForDismissedController(_di_UIViewController dismissed) = 0 ;
	virtual void * __cdecl interactionControllerForPresentation(void * animator) = 0 ;
	virtual void * __cdecl interactionControllerForDismissal(void * animator) = 0 ;
	virtual _di_UIPresentationController __cdecl presentationControllerForPresentedViewController(_di_UIViewController presented, _di_UIViewController presentingViewController, _di_UIViewController sourceViewController) = 0 ;
};

__interface  INTERFACE_UUID("{DF4074D3-6A13-4867-ABC0-B313E407EBD0}") UIBarPositioning  : public Macapi::Objectivec::IObjectiveC 
{
	virtual long __cdecl barPosition() = 0 ;
};

__interface  INTERFACE_UUID("{42ACE160-C992-4334-A1AD-5309724E1C3F}") UIBarPositioningDelegate  : public Macapi::Objectivec::IObjectiveC 
{
	virtual long __cdecl positionForBar(void * bar) = 0 ;
};

__interface  INTERFACE_UUID("{BBFAC156-DFC5-437B-A320-AC9C43C853B3}") UICollectionViewDataSource  : public Macapi::Objectivec::IObjectiveC 
{
	virtual long __cdecl collectionViewNumberOfItemsInSection(_di_UICollectionView collectionView, long numberOfItemsInSection) = 0 ;
	virtual _di_UICollectionViewCell __cdecl collectionViewCellForItemAtIndexPath(_di_UICollectionView collectionView, Iosapi::Foundation::_di_NSIndexPath cellForItemAtIndexPath) = 0 ;
	virtual long __cdecl numberOfSectionsInCollectionView(_di_UICollectionView collectionView) = 0 ;
	virtual _di_UICollectionReusableView __cdecl collectionViewViewForSupplementaryElementOfKindAtIndexPath(_di_UICollectionView collectionView, Iosapi::Foundation::_di_NSString viewForSupplementaryElementOfKind, Iosapi::Foundation::_di_NSIndexPath atIndexPath) = 0 ;
};

__interface  INTERFACE_UUID("{F25A1FE1-A89B-4DA6-9E8C-3BE4B3557993}") UICollectionViewDelegate  : public Macapi::Objectivec::IObjectiveC 
{
	virtual bool __cdecl collectionViewShouldHighlightItemAtIndexPath(_di_UICollectionView collectionView, Iosapi::Foundation::_di_NSIndexPath shouldHighlightItemAtIndexPath) = 0 ;
	virtual void __cdecl collectionViewDidHighlightItemAtIndexPath(_di_UICollectionView collectionView, Iosapi::Foundation::_di_NSIndexPath didHighlightItemAtIndexPath) = 0 ;
	virtual void __cdecl collectionViewDidUnhighlightItemAtIndexPath(_di_UICollectionView collectionView, Iosapi::Foundation::_di_NSIndexPath didUnhighlightItemAtIndexPath) = 0 ;
	virtual bool __cdecl collectionViewShouldSelectItemAtIndexPath(_di_UICollectionView collectionView, Iosapi::Foundation::_di_NSIndexPath shouldSelectItemAtIndexPath) = 0 ;
	virtual bool __cdecl collectionViewShouldDeselectItemAtIndexPath(_di_UICollectionView collectionView, Iosapi::Foundation::_di_NSIndexPath shouldDeselectItemAtIndexPath) = 0 ;
	virtual void __cdecl collectionViewDidSelectItemAtIndexPath(_di_UICollectionView collectionView, Iosapi::Foundation::_di_NSIndexPath didSelectItemAtIndexPath) = 0 ;
	virtual void __cdecl collectionViewDidDeselectItemAtIndexPath(_di_UICollectionView collectionView, Iosapi::Foundation::_di_NSIndexPath didDeselectItemAtIndexPath) = 0 ;
	virtual void __cdecl collectionViewDidEndDisplayingCellForItemAtIndexPath(_di_UICollectionView collectionView, _di_UICollectionViewCell didEndDisplayingCell, Iosapi::Foundation::_di_NSIndexPath forItemAtIndexPath) = 0 ;
	virtual void __cdecl collectionViewDidEndDisplayingSupplementaryViewForElementOfKindAtIndexPath(_di_UICollectionView collectionView, _di_UICollectionReusableView didEndDisplayingSupplementaryView, Iosapi::Foundation::_di_NSString forElementOfKind, Iosapi::Foundation::_di_NSIndexPath atIndexPath) = 0 ;
	virtual bool __cdecl collectionViewShouldShowMenuForItemAtIndexPath(_di_UICollectionView collectionView, Iosapi::Foundation::_di_NSIndexPath shouldShowMenuForItemAtIndexPath) = 0 ;
	virtual bool __cdecl collectionViewCanPerformActionForItemAtIndexPathWithSender(_di_UICollectionView collectionView, void * canPerformAction, Iosapi::Foundation::_di_NSIndexPath forItemAtIndexPath, void * withSender) = 0 ;
	virtual void __cdecl collectionViewPerformActionForItemAtIndexPathWithSender(_di_UICollectionView collectionView, void * performAction, Iosapi::Foundation::_di_NSIndexPath forItemAtIndexPath, void * withSender) = 0 ;
	virtual _di_UICollectionViewTransitionLayout __cdecl collectionViewTransitionLayoutForOldLayoutNewLayout(_di_UICollectionView collectionView, _di_UICollectionViewLayout transitionLayoutForOldLayout, _di_UICollectionViewLayout newLayout) = 0 ;
};

__interface  INTERFACE_UUID("{BA93BCB0-3750-426F-9AFA-14541A08FC10}") UICollectionViewDelegateFlowLayout  : public Macapi::Objectivec::IObjectiveC 
{
	virtual Iosapi::Foundation::NSSize __cdecl collectionViewLayoutSizeForItemAtIndexPath(_di_UICollectionView collectionView, _di_UICollectionViewLayout layout, Iosapi::Foundation::_di_NSIndexPath sizeForItemAtIndexPath) = 0 ;
	virtual UIEdgeInsets __cdecl collectionViewLayoutInsetForSectionAtIndex(_di_UICollectionView collectionView, _di_UICollectionViewLayout layout, long insetForSectionAtIndex) = 0 ;
	virtual double __cdecl collectionViewLayoutMinimumLineSpacingForSectionAtIndex(_di_UICollectionView collectionView, _di_UICollectionViewLayout layout, long minimumLineSpacingForSectionAtIndex) = 0 ;
	virtual double __cdecl collectionViewLayoutMinimumInteritemSpacingForSectionAtIndex(_di_UICollectionView collectionView, _di_UICollectionViewLayout layout, long minimumInteritemSpacingForSectionAtIndex) = 0 ;
	virtual Iosapi::Foundation::NSSize __cdecl collectionViewLayoutReferenceSizeForHeaderInSection(_di_UICollectionView collectionView, _di_UICollectionViewLayout layout, long referenceSizeForHeaderInSection) = 0 ;
	virtual Iosapi::Foundation::NSSize __cdecl collectionViewLayoutReferenceSizeForFooterInSection(_di_UICollectionView collectionView, _di_UICollectionViewLayout layout, long referenceSizeForFooterInSection) = 0 ;
};

__interface  INTERFACE_UUID("{F529FE94-2D8A-4C20-BF2A-ED14C7A00CB1}") UIDocumentInteractionControllerDelegate  : public Macapi::Objectivec::IObjectiveC 
{
	virtual _di_UIViewController __cdecl documentInteractionControllerViewControllerForPreview(_di_UIDocumentInteractionController controller) = 0 ;
	virtual Iosapi::Foundation::NSRect __cdecl documentInteractionControllerRectForPreview(_di_UIDocumentInteractionController controller) = 0 ;
	virtual _di_UIView __cdecl documentInteractionControllerViewForPreview(_di_UIDocumentInteractionController controller) = 0 ;
	virtual void __cdecl documentInteractionControllerWillBeginPreview(_di_UIDocumentInteractionController controller) = 0 ;
	virtual void __cdecl documentInteractionControllerDidEndPreview(_di_UIDocumentInteractionController controller) = 0 ;
	virtual void __cdecl documentInteractionControllerWillPresentOptionsMenu(_di_UIDocumentInteractionController controller) = 0 ;
	virtual void __cdecl documentInteractionControllerDidDismissOptionsMenu(_di_UIDocumentInteractionController controller) = 0 ;
	virtual void __cdecl documentInteractionControllerWillPresentOpenInMenu(_di_UIDocumentInteractionController controller) = 0 ;
	virtual void __cdecl documentInteractionControllerDidDismissOpenInMenu(_di_UIDocumentInteractionController controller) = 0 ;
	virtual void __cdecl documentInteractionControllerWillBeginSendingToApplication(_di_UIDocumentInteractionController controller, Iosapi::Foundation::_di_NSString willBeginSendingToApplication) = 0 ;
	virtual void __cdecl documentInteractionControllerDidEndSendingToApplication(_di_UIDocumentInteractionController controller, Iosapi::Foundation::_di_NSString didEndSendingToApplication) = 0 ;
	virtual bool __cdecl documentInteractionControllerCanPerformAction(_di_UIDocumentInteractionController controller, void * canPerformAction) = 0 ;
	virtual bool __cdecl documentInteractionControllerPerformAction(_di_UIDocumentInteractionController controller, void * performAction) = 0 ;
};

__interface  INTERFACE_UUID("{02302349-DF18-4FCD-9621-3A3C80A96FBB}") UINavigationControllerDelegate  : public Macapi::Objectivec::IObjectiveC 
{
	virtual void __cdecl navigationControllerWillShowViewControllerAnimated(_di_UINavigationController navigationController, _di_UIViewController willShowViewController, bool animated) = 0 ;
	virtual void __cdecl navigationControllerDidShowViewControllerAnimated(_di_UINavigationController navigationController, _di_UIViewController didShowViewController, bool animated) = 0 ;
	virtual unsigned long __cdecl navigationControllerSupportedInterfaceOrientations(_di_UINavigationController navigationController) = 0 ;
	virtual long __cdecl navigationControllerPreferredInterfaceOrientationForPresentation(_di_UINavigationController navigationController) = 0 ;
	virtual void * __cdecl navigationControllerInteractionControllerForAnimationController(_di_UINavigationController navigationController, void * interactionControllerForAnimationController) = 0 ;
	virtual void * __cdecl navigationControllerAnimationControllerForOperationFromViewControllerToViewController(_di_UINavigationController navigationController, long animationControllerForOperation, _di_UIViewController fromViewController, _di_UIViewController toViewController) = 0 ;
};

__interface  INTERFACE_UUID("{A370851F-9D20-46CD-B047-4618A77D9391}") UIViewControllerInteractiveTransitioning  : public Macapi::Objectivec::IObjectiveC 
{
	virtual void __cdecl startInteractiveTransition(void * transitionContext) = 0 ;
	virtual double __cdecl completionSpeed() = 0 ;
	virtual long __cdecl completionCurve() = 0 ;
};

__interface  INTERFACE_UUID("{0B020D70-DF9E-43AC-ACED-C4A29EDC2DCA}") UIViewControllerAnimatedTransitioning  : public Macapi::Objectivec::IObjectiveC 
{
	virtual double __cdecl transitionDuration(void * transitionContext) = 0 ;
	virtual void __cdecl animateTransition(void * transitionContext) = 0 ;
	virtual void __cdecl animationEnded(bool transitionCompleted) = 0 ;
};

__interface  INTERFACE_UUID("{8765B7AA-89D6-4DF3-9518-8BEAEF783B0C}") UINavigationBarDelegate  : public Macapi::Objectivec::IObjectiveC 
{
	virtual bool __cdecl navigationBarShouldPushItem(_di_UINavigationBar navigationBar, _di_UINavigationItem shouldPushItem) = 0 ;
	virtual void __cdecl navigationBarDidPushItem(_di_UINavigationBar navigationBar, _di_UINavigationItem didPushItem) = 0 ;
	virtual bool __cdecl navigationBarShouldPopItem(_di_UINavigationBar navigationBar, _di_UINavigationItem shouldPopItem) = 0 ;
	virtual void __cdecl navigationBarDidPopItem(_di_UINavigationBar navigationBar, _di_UINavigationItem didPopItem) = 0 ;
};

__interface  INTERFACE_UUID("{0E6B148B-3E36-43D2-9472-F81635E92A5D}") UIPageViewControllerDelegate  : public Macapi::Objectivec::IObjectiveC 
{
	virtual void __cdecl pageViewControllerWillTransitionToViewControllers(_di_UIPageViewController pageViewController, Iosapi::Foundation::_di_NSArray willTransitionToViewControllers) = 0 ;
	virtual void __cdecl pageViewControllerDidFinishAnimatingPreviousViewControllersTransitionCompleted(_di_UIPageViewController pageViewController, bool didFinishAnimating, Iosapi::Foundation::_di_NSArray previousViewControllers, bool transitionCompleted) = 0 ;
	virtual long __cdecl pageViewControllerSpineLocationForInterfaceOrientation(_di_UIPageViewController pageViewController, long spineLocationForInterfaceOrientation) = 0 ;
	virtual unsigned long __cdecl pageViewControllerSupportedInterfaceOrientations(_di_UIPageViewController pageViewController) = 0 ;
	virtual long __cdecl pageViewControllerPreferredInterfaceOrientationForPresentation(_di_UIPageViewController pageViewController) = 0 ;
};

__interface  INTERFACE_UUID("{54722E32-E25B-441E-BC5D-BD462C50CFA9}") UIPageViewControllerDataSource  : public Macapi::Objectivec::IObjectiveC 
{
	virtual _di_UIViewController __cdecl pageViewControllerViewControllerBeforeViewController(_di_UIPageViewController pageViewController, _di_UIViewController viewControllerBeforeViewController) = 0 ;
	virtual _di_UIViewController __cdecl pageViewControllerViewControllerAfterViewController(_di_UIPageViewController pageViewController, _di_UIViewController viewControllerAfterViewController) = 0 ;
	virtual long __cdecl presentationCountForPageViewController(_di_UIPageViewController pageViewController) = 0 ;
	virtual long __cdecl presentationIndexForPageViewController(_di_UIPageViewController pageViewController) = 0 ;
};

__interface  INTERFACE_UUID("{19029A2D-F062-42B2-8D9A-08CCBE376508}") UIPrintInteractionControllerDelegate  : public Macapi::Objectivec::IObjectiveC 
{
	virtual _di_UIViewController __cdecl printInteractionControllerParentViewController(_di_UIPrintInteractionController printInteractionController) = 0 ;
	virtual _di_UIPrintPaper __cdecl printInteractionControllerChoosePaper(_di_UIPrintInteractionController printInteractionController, Iosapi::Foundation::_di_NSArray choosePaper) = 0 ;
	virtual void __cdecl printInteractionControllerWillPresentPrinterOptions(_di_UIPrintInteractionController printInteractionController) = 0 ;
	virtual void __cdecl printInteractionControllerDidPresentPrinterOptions(_di_UIPrintInteractionController printInteractionController) = 0 ;
	virtual void __cdecl printInteractionControllerWillDismissPrinterOptions(_di_UIPrintInteractionController printInteractionController) = 0 ;
	virtual void __cdecl printInteractionControllerDidDismissPrinterOptions(_di_UIPrintInteractionController printInteractionController) = 0 ;
	virtual void __cdecl printInteractionControllerWillStartJob(_di_UIPrintInteractionController printInteractionController) = 0 ;
	virtual void __cdecl printInteractionControllerDidFinishJob(_di_UIPrintInteractionController printInteractionController) = 0 ;
	virtual double __cdecl printInteractionControllerCutLengthForPaper(_di_UIPrintInteractionController printInteractionController, _di_UIPrintPaper cutLengthForPaper) = 0 ;
};

__interface  INTERFACE_UUID("{3BC2936D-3FEF-4B05-BF8A-8E3E12AD7BB8}") UISearchBarDelegate  : public Macapi::Objectivec::IObjectiveC 
{
	virtual bool __cdecl searchBarShouldBeginEditing(_di_UISearchBar searchBar) = 0 ;
	virtual void __cdecl searchBarTextDidBeginEditing(_di_UISearchBar searchBar) = 0 ;
	virtual bool __cdecl searchBarShouldEndEditing(_di_UISearchBar searchBar) = 0 ;
	virtual void __cdecl searchBarTextDidEndEditing(_di_UISearchBar searchBar) = 0 ;
	virtual void __cdecl searchBarTextDidChange(_di_UISearchBar searchBar, Iosapi::Foundation::_di_NSString textDidChange) = 0 ;
	virtual bool __cdecl searchBarShouldChangeTextInRangeReplacementText(_di_UISearchBar searchBar, Iosapi::Foundation::NSRange shouldChangeTextInRange, Iosapi::Foundation::_di_NSString replacementText) = 0 ;
	virtual void __cdecl searchBarSearchButtonClicked(_di_UISearchBar searchBar) = 0 ;
	virtual void __cdecl searchBarBookmarkButtonClicked(_di_UISearchBar searchBar) = 0 ;
	virtual void __cdecl searchBarCancelButtonClicked(_di_UISearchBar searchBar) = 0 ;
	virtual void __cdecl searchBarResultsListButtonClicked(_di_UISearchBar searchBar) = 0 ;
	virtual void __cdecl searchBarSelectedScopeButtonIndexDidChange(_di_UISearchBar searchBar, long selectedScopeButtonIndexDidChange) = 0 ;
};

__interface  INTERFACE_UUID("{04DA4B86-FE96-4345-B9F3-E75AE64480A6}") UISearchDisplayDelegate  : public Macapi::Objectivec::IObjectiveC 
{
	virtual void __cdecl searchDisplayControllerWillBeginSearch(_di_UISearchDisplayController controller) = 0 ;
	virtual void __cdecl searchDisplayControllerDidBeginSearch(_di_UISearchDisplayController controller) = 0 ;
	virtual void __cdecl searchDisplayControllerWillEndSearch(_di_UISearchDisplayController controller) = 0 ;
	virtual void __cdecl searchDisplayControllerDidEndSearch(_di_UISearchDisplayController controller) = 0 ;
	virtual void __cdecl searchDisplayControllerDidLoadSearchResultsTableView(_di_UISearchDisplayController controller, _di_UITableView didLoadSearchResultsTableView) = 0 ;
	virtual void __cdecl searchDisplayControllerWillUnloadSearchResultsTableView(_di_UISearchDisplayController controller, _di_UITableView willUnloadSearchResultsTableView) = 0 ;
	virtual void __cdecl searchDisplayControllerWillShowSearchResultsTableView(_di_UISearchDisplayController controller, _di_UITableView willShowSearchResultsTableView) = 0 ;
	virtual void __cdecl searchDisplayControllerDidShowSearchResultsTableView(_di_UISearchDisplayController controller, _di_UITableView didShowSearchResultsTableView) = 0 ;
	virtual void __cdecl searchDisplayControllerWillHideSearchResultsTableView(_di_UISearchDisplayController controller, _di_UITableView willHideSearchResultsTableView) = 0 ;
	virtual void __cdecl searchDisplayControllerDidHideSearchResultsTableView(_di_UISearchDisplayController controller, _di_UITableView didHideSearchResultsTableView) = 0 ;
	virtual bool __cdecl searchDisplayControllerShouldReloadTableForSearchString(_di_UISearchDisplayController controller, Iosapi::Foundation::_di_NSString shouldReloadTableForSearchString) = 0 ;
	virtual bool __cdecl searchDisplayControllerShouldReloadTableForSearchScope(_di_UISearchDisplayController controller, long shouldReloadTableForSearchScope) = 0 ;
};

__interface  INTERFACE_UUID("{6188711E-51CB-4400-9DC9-207DE7200AE6}") UISplitViewControllerDelegate  : public Macapi::Objectivec::IObjectiveC 
{
	virtual void __cdecl splitViewControllerWillHideViewControllerWithBarButtonItemForPopoverController(_di_UISplitViewController svc, _di_UIViewController willHideViewController, _di_UIBarButtonItem withBarButtonItem, _di_UIPopoverController forPopoverController) = 0 ;
	virtual void __cdecl splitViewControllerWillShowViewControllerInvalidatingBarButtonItem(_di_UISplitViewController svc, _di_UIViewController willShowViewController, _di_UIBarButtonItem invalidatingBarButtonItem) = 0 ;
	virtual void __cdecl splitViewControllerPopoverControllerWillPresentViewController(_di_UISplitViewController svc, _di_UIPopoverController popoverController, _di_UIViewController willPresentViewController) = 0 ;
	virtual bool __cdecl splitViewControllerShouldHideViewControllerInOrientation(_di_UISplitViewController svc, _di_UIViewController shouldHideViewController, long inOrientation) = 0 ;
	virtual unsigned long __cdecl splitViewControllerSupportedInterfaceOrientations(_di_UISplitViewController splitViewController) = 0 ;
	virtual long __cdecl splitViewControllerPreferredInterfaceOrientationForPresentation(_di_UISplitViewController splitViewController) = 0 ;
};

__interface  INTERFACE_UUID("{D6BA6D3E-3DAE-4D48-B3D2-001EFFA98D91}") UITabBarDelegate  : public Macapi::Objectivec::IObjectiveC 
{
	virtual void __cdecl tabBarDidSelectItem(_di_UITabBar tabBar, _di_UITabBarItem didSelectItem) = 0 ;
	virtual void __cdecl tabBarWillBeginCustomizingItems(_di_UITabBar tabBar, Iosapi::Foundation::_di_NSArray willBeginCustomizingItems) = 0 ;
	virtual void __cdecl tabBarDidBeginCustomizingItems(_di_UITabBar tabBar, Iosapi::Foundation::_di_NSArray didBeginCustomizingItems) = 0 ;
	virtual void __cdecl tabBarWillEndCustomizingItemsChanged(_di_UITabBar tabBar, Iosapi::Foundation::_di_NSArray willEndCustomizingItems, bool changed) = 0 ;
	virtual void __cdecl tabBarDidEndCustomizingItemsChanged(_di_UITabBar tabBar, Iosapi::Foundation::_di_NSArray didEndCustomizingItems, bool changed) = 0 ;
};

__interface  INTERFACE_UUID("{D63FF74B-237B-4E4E-B389-278F10FDBB66}") UIViewControllerTransitionCoordinatorContext  : public Macapi::Objectivec::IObjectiveC 
{
	virtual bool __cdecl isAnimated() = 0 ;
	virtual long __cdecl presentationStyle() = 0 ;
	virtual bool __cdecl initiallyInteractive() = 0 ;
	virtual bool __cdecl isInteractive() = 0 ;
	virtual bool __cdecl isCancelled() = 0 ;
	virtual double __cdecl transitionDuration() = 0 ;
	virtual double __cdecl percentComplete() = 0 ;
	virtual double __cdecl completionVelocity() = 0 ;
	virtual long __cdecl completionCurve() = 0 ;
	virtual _di_UIViewController __cdecl viewControllerForKey(Iosapi::Foundation::_di_NSString key) = 0 ;
	virtual _di_UIView __cdecl containerView() = 0 ;
};

__interface  INTERFACE_UUID("{53044E27-FFC8-4209-94E4-61CFBF746678}") UIViewControllerTransitionCoordinator  : public Macapi::Objectivec::IObjectiveC 
{
	virtual bool __cdecl animateAlongsideTransition(TUIKitAnimation animation, TUIKitAnimation completion) = 0 ;
	virtual bool __cdecl animateAlongsideTransitionInView(_di_UIView view, TUIKitAnimation animation, TUIKitAnimation completion) = 0 ;
	virtual void __cdecl notifyWhenInteractionEndsUsingBlock(TUIKitAnimation handler) = 0 ;
};

__interface  INTERFACE_UUID("{043C224D-E785-4013-8463-9E4DA49A9088}") UIViewControllerContextTransitioning  : public Macapi::Objectivec::IObjectiveC 
{
	virtual _di_UIView __cdecl containerView() = 0 ;
	virtual bool __cdecl isAnimated() = 0 ;
	virtual bool __cdecl isInteractive() = 0 ;
	virtual bool __cdecl transitionWasCancelled() = 0 ;
	virtual long __cdecl presentationStyle() = 0 ;
	virtual void __cdecl updateInteractiveTransition(double percentComplete) = 0 ;
	virtual void __cdecl finishInteractiveTransition() = 0 ;
	virtual void __cdecl cancelInteractiveTransition() = 0 ;
	virtual void __cdecl completeTransition(bool didComplete) = 0 ;
	virtual _di_UIViewController __cdecl viewControllerForKey(Iosapi::Foundation::_di_NSString key) = 0 ;
	virtual Iosapi::Foundation::NSRect __cdecl initialFrameForViewController(_di_UIViewController vc) = 0 ;
	virtual Iosapi::Foundation::NSRect __cdecl finalFrameForViewController(_di_UIViewController vc) = 0 ;
};

__interface  INTERFACE_UUID("{82184D7D-ECFF-498C-A431-AA7294EB54D6}") UITabBarControllerDelegate  : public Macapi::Objectivec::IObjectiveC 
{
	virtual bool __cdecl tabBarControllerShouldSelectViewController(_di_UITabBarController tabBarController, _di_UIViewController shouldSelectViewController) = 0 ;
	virtual void __cdecl tabBarControllerDidSelectViewController(_di_UITabBarController tabBarController, _di_UIViewController didSelectViewController) = 0 ;
	virtual void __cdecl tabBarControllerWillBeginCustomizingViewControllers(_di_UITabBarController tabBarController, Iosapi::Foundation::_di_NSArray willBeginCustomizingViewControllers) = 0 ;
	virtual void __cdecl tabBarControllerWillEndCustomizingViewControllersChanged(_di_UITabBarController tabBarController, Iosapi::Foundation::_di_NSArray willEndCustomizingViewControllers, bool changed) = 0 ;
	virtual void __cdecl tabBarControllerDidEndCustomizingViewControllersChanged(_di_UITabBarController tabBarController, Iosapi::Foundation::_di_NSArray didEndCustomizingViewControllers, bool changed) = 0 ;
	virtual unsigned long __cdecl tabBarControllerSupportedInterfaceOrientations(_di_UITabBarController tabBarController) = 0 ;
	virtual long __cdecl tabBarControllerPreferredInterfaceOrientationForPresentation(_di_UITabBarController tabBarController) = 0 ;
	virtual void * __cdecl tabBarControllerInteractionControllerForAnimationController(_di_UITabBarController tabBarController, void * interactionControllerForAnimationController) = 0 ;
	virtual void * __cdecl tabBarControllerAnimationControllerForTransitionFromViewControllerToViewController(_di_UITabBarController tabBarController, _di_UIViewController animationControllerForTransitionFromViewController, _di_UIViewController toViewController) = 0 ;
};

__interface  INTERFACE_UUID("{D22276B3-5E9C-49F4-8A63-0062F9221EC2}") UITextViewDelegate  : public Macapi::Objectivec::IObjectiveC 
{
	virtual bool __cdecl textViewShouldBeginEditing(_di_UITextView textView) = 0 ;
	virtual bool __cdecl textViewShouldEndEditing(_di_UITextView textView) = 0 ;
	virtual void __cdecl textViewDidBeginEditing(_di_UITextView textView) = 0 ;
	virtual void __cdecl textViewDidEndEditing(_di_UITextView textView) = 0 ;
	virtual bool __cdecl textViewShouldChangeTextInRangeReplacementText(_di_UITextView textView, Iosapi::Foundation::NSRange shouldChangeTextInRange, Iosapi::Foundation::_di_NSString replacementText) = 0 ;
	virtual void __cdecl textViewDidChange(_di_UITextView textView) = 0 ;
	virtual void __cdecl textViewDidChangeSelection(_di_UITextView textView) = 0 ;
	virtual bool __cdecl textViewShouldInteractWithURLInRange(_di_UITextView textView, Iosapi::Foundation::_di_NSURL shouldInteractWithURL, Iosapi::Foundation::NSRange inRange) = 0 ;
	virtual bool __cdecl textViewShouldInteractWithTextAttachmentInRange(_di_UITextView textView, _di_NSTextAttachment shouldInteractWithTextAttachment, Iosapi::Foundation::NSRange inRange) = 0 ;
};

__interface  INTERFACE_UUID("{6A6F83DF-0E08-4919-9093-6868B94C8385}") UIToolbarDelegate  : public Macapi::Objectivec::IObjectiveC 
{
	
};

__interface  INTERFACE_UUID("{54092293-E863-425F-ABF0-6D4AD90B1680}") UIVideoEditorControllerDelegate  : public Macapi::Objectivec::IObjectiveC 
{
	virtual void __cdecl videoEditorControllerDidSaveEditedVideoToPath(_di_UIVideoEditorController editor, Iosapi::Foundation::_di_NSString didSaveEditedVideoToPath) = 0 ;
	virtual void __cdecl videoEditorControllerDidFailWithError(_di_UIVideoEditorController editor, Iosapi::Foundation::_di_NSError didFailWithError) = 0 ;
	virtual void __cdecl videoEditorControllerDidCancel(_di_UIVideoEditorController editor) = 0 ;
};

__interface  INTERFACE_UUID("{9F542F74-4B8D-4CE4-97F8-0AA5EB1D4A8D}") UIDynamicAnimatorDelegate  : public Macapi::Objectivec::IObjectiveC 
{
	virtual void __cdecl dynamicAnimatorWillResume(_di_UIDynamicAnimator animator) = 0 ;
	virtual void __cdecl dynamicAnimatorDidPause(_di_UIDynamicAnimator animator) = 0 ;
};

__interface  INTERFACE_UUID("{8EBC2DEB-836B-4D88-B901-5116ED953162}") UICollisionBehaviorDelegate  : public Macapi::Objectivec::IObjectiveC 
{
	virtual void __cdecl collisionBehaviorBeganContactForItemWithItemAtPoint(_di_UICollisionBehavior behavior, void * beganContactForItem, void * withItem, Iosapi::Foundation::NSPoint atPoint) = 0 ;
	virtual void __cdecl collisionBehaviorEndedContactForItemWithItem(_di_UICollisionBehavior behavior, void * endedContactForItem, void * withItem) = 0 ;
	virtual void __cdecl collisionBehaviorBeganContactForItemWithBoundaryIdentifierAtPoint(_di_UICollisionBehavior behavior, void * beganContactForItem, void * withBoundaryIdentifier, Iosapi::Foundation::NSPoint atPoint) = 0 ;
	virtual void __cdecl collisionBehaviorEndedContactForItemWithBoundaryIdentifier(_di_UICollisionBehavior behavior, void * endedContactForItem, void * withBoundaryIdentifier) = 0 ;
};

__interface  INTERFACE_UUID("{9ADE9E52-71BE-4967-9615-C15BED273D7A}") UIContentContainer  : public Macapi::Objectivec::IObjectiveC 
{
	virtual Iosapi::Foundation::NSSize __cdecl preferredContentSize() = 0 ;
	virtual void __cdecl preferredContentSizeDidChangeForChildContentContainer(void * container) = 0 ;
	virtual void __cdecl systemLayoutFittingSizeDidChangeForChildContentContainer(void * container) = 0 ;
	virtual Iosapi::Foundation::NSSize __cdecl sizeForChildContentContainer(void * container, Iosapi::Foundation::NSSize withParentContainerSize) = 0 ;
	virtual void __cdecl viewWillTransitionToSize(Iosapi::Foundation::NSSize size, void * withTransitionCoordinator) = 0 ;
	virtual void __cdecl willTransitionToTraitCollection(_di_UITraitCollection newCollection, void * withTransitionCoordinator) = 0 ;
};

__interface  INTERFACE_UUID("{4F479854-D7A2-4516-BECE-BBA2800323FF}") UITextDocumentProxy  : public Macapi::Objectivec::IObjectiveC 
{
	virtual Iosapi::Foundation::_di_NSString __cdecl documentContextBeforeInput() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl documentContextAfterInput() = 0 ;
	virtual void __cdecl adjustTextPositionByCharacterOffset(long offset) = 0 ;
};

__interface  INTERFACE_UUID("{3B1C6A10-8ED0-410D-A77F-A8FF4C2E7840}") UIPopoverBackgroundViewMethods  : public Macapi::Objectivec::IObjectiveC 
{
	virtual double __cdecl arrowBase() = 0 ;
	virtual UIEdgeInsets __cdecl contentViewInsets() = 0 ;
	virtual double __cdecl arrowHeight() = 0 ;
};

__interface  INTERFACE_UUID("{847C96D6-609B-4BBE-8D37-49108E3AE969}") UIPrinterPickerControllerDelegate  : public Macapi::Objectivec::IObjectiveC 
{
	virtual _di_UIViewController __cdecl printerPickerControllerParentViewController(_di_UIPrinterPickerController printerPickerController) = 0 ;
	virtual bool __cdecl printerPickerController(_di_UIPrinterPickerController printerPickerController, _di_UIPrinter shouldShowPrinter) = 0 ;
	virtual void __cdecl printerPickerControllerWillPresent(_di_UIPrinterPickerController printerPickerController) = 0 ;
	virtual void __cdecl printerPickerControllerDidPresent(_di_UIPrinterPickerController printerPickerController) = 0 ;
	virtual void __cdecl printerPickerControllerWillDismiss(_di_UIPrinterPickerController printerPickerController) = 0 ;
	virtual void __cdecl printerPickerControllerDidDismiss(_di_UIPrinterPickerController printerPickerController) = 0 ;
	virtual void __cdecl printerPickerControllerDidSelectPrinter(_di_UIPrinterPickerController printerPickerController) = 0 ;
};

__interface  INTERFACE_UUID("{173BB3F6-ED9D-4C00-84BC-37E7A245B6A1}") UIAdaptivePresentationControllerDelegate  : public Macapi::Objectivec::IObjectiveC 
{
	virtual long __cdecl adaptivePresentationStyleForPresentationController(_di_UIPresentationController controller) = 0 ;
	virtual _di_UIViewController __cdecl presentationController(_di_UIPresentationController controller, long viewControllerForAdaptivePresentationStyle) = 0 ;
};

__interface  INTERFACE_UUID("{3A8C75D8-C5B6-4B76-8445-74A60C85DEED}") UISearchControllerDelegate  : public Macapi::Objectivec::IObjectiveC 
{
	virtual void __cdecl willPresentSearchController(_di_UISearchController searchController) = 0 ;
	virtual void __cdecl didPresentSearchController(_di_UISearchController searchController) = 0 ;
	virtual void __cdecl willDismissSearchController(_di_UISearchController searchController) = 0 ;
	virtual void __cdecl didDismissSearchController(_di_UISearchController searchController) = 0 ;
	virtual void __cdecl presentSearchController(_di_UISearchController searchController) = 0 ;
};

__interface  INTERFACE_UUID("{B00A93D8-CF2E-4375-829D-E681D67DAD3A}") UISearchResultsUpdating  : public Macapi::Objectivec::IObjectiveC 
{
	virtual void __cdecl updateSearchResultsForSearchController(_di_UISearchController searchController) = 0 ;
};

__interface  INTERFACE_UUID("{505779DC-D04C-45E2-A085-57FE8585E8A6}") UIPopoverPresentationControllerDelegate  : public Macapi::Objectivec::IObjectiveC 
{
	virtual void __cdecl prepareForPopoverPresentation(_di_UIPopoverPresentationController popoverPresentationController) = 0 ;
	virtual bool __cdecl popoverPresentationControllerShouldDismissPopover(_di_UIPopoverPresentationController popoverPresentationController) = 0 ;
	virtual void __cdecl popoverPresentationControllerDidDismissPopover(_di_UIPopoverPresentationController popoverPresentationController) = 0 ;
	virtual void __cdecl popoverPresentationController(_di_UIPopoverPresentationController popoverPresentationController, void * willRepositionPopoverToRect, _di_UIView inView) = 0 ;
};

__interface  INTERFACE_UUID("{0D73EA79-9F6F-4598-9973-6E511EA775AF}") UIContextMenuConfigurationClass  : public Iosapi::Quartzcore::NSObjectClass 
{
	virtual void * __cdecl configurationWithIdentifier(void * identifier, UIContextMenuContentPreviewProvider previewProvider, UIContextMenuActionProvider actionProvider) = 0 ;
};

__interface  INTERFACE_UUID("{ABB556FC-14FB-4E3B-B181-08FCE63B1641}") UIContextMenuConfiguration  : public Iosapi::Foundation::NSObject 
{
	virtual void * __cdecl identifier() = 0 ;
};

class PASCALIMPLEMENTATION TUIContextMenuConfiguration : public Macapi::Objectivec::TOCGenericImport__2<_di_UIContextMenuConfigurationClass,_di_UIContextMenuConfiguration>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UIContextMenuConfigurationClass,_di_UIContextMenuConfiguration> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUIContextMenuConfiguration(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UIContextMenuConfigurationClass,_di_UIContextMenuConfiguration>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUIContextMenuConfiguration() { }
	
};


__interface  INTERFACE_UUID("{5470144B-6B6C-4E5F-AF8B-1D1C649F4B66}") UIMenuElementClass  : public Iosapi::Quartzcore::NSObjectClass 
{
	virtual void * __cdecl New() = 0 ;
};

__interface  INTERFACE_UUID("{30E9E608-634B-4451-A794-BCDA398192E3}") UIMenuElement  : public Iosapi::Foundation::NSObject 
{
	virtual _di_UIImage __cdecl image() = 0 ;
	virtual void * __cdecl initWithCoder(Iosapi::Foundation::_di_NSCoder coder) = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl title() = 0 ;
};

class PASCALIMPLEMENTATION TUIMenuElement : public Macapi::Objectivec::TOCGenericImport__2<_di_UIMenuElementClass,_di_UIMenuElement>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UIMenuElementClass,_di_UIMenuElement> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUIMenuElement(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UIMenuElementClass,_di_UIMenuElement>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUIMenuElement() { }
	
};


__interface  INTERFACE_UUID("{938C530B-5237-4361-8E3E-C71687791161}") UIMenuClass  : public UIMenuElementClass 
{
	virtual _di_UIMenu __cdecl menuWithTitle(Iosapi::Foundation::_di_NSString title, _di_UIImage image, Iosapi::Foundation::_di_NSString identifier, long options, Iosapi::Foundation::_di_NSArray children) = 0 /* overload */;
	virtual _di_UIMenu __cdecl menuWithTitle(Iosapi::Foundation::_di_NSString title, Iosapi::Foundation::_di_NSArray children) = 0 /* overload */;
	HIDESBASE virtual void * __cdecl New() = 0 ;
};

__interface  INTERFACE_UUID("{324F4C54-8E2B-4599-A3E8-7F1C0DA549A4}") UIMenu  : public UIMenuElement 
{
	virtual Iosapi::Foundation::_di_NSArray __cdecl children() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl identifier() = 0 ;
	HIDESBASE virtual void * __cdecl initWithCoder(Iosapi::Foundation::_di_NSCoder coder) = 0 ;
	virtual _di_UIMenu __cdecl menuByReplacingChildren(Iosapi::Foundation::_di_NSArray newChildren) = 0 ;
	virtual long __cdecl options() = 0 ;
};

class PASCALIMPLEMENTATION TUIMenu : public Macapi::Objectivec::TOCGenericImport__2<_di_UIMenuClass,_di_UIMenu>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UIMenuClass,_di_UIMenu> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUIMenu(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UIMenuClass,_di_UIMenu>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUIMenu() { }
	
};


__interface  INTERFACE_UUID("{5663FD92-8760-4BD3-9359-91EE9966D527}") UIAlertActionClass  : public Iosapi::Quartzcore::NSObjectClass 
{
	virtual void * __cdecl actionWithTitle(Iosapi::Foundation::_di_NSString title, long style, TUIKitHandler handler) = 0 ;
};

__interface  INTERFACE_UUID("{8DF95F0B-4F59-4AD5-BFE5-1CAF92937844}") UIAlertAction  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::_di_NSString __cdecl title() = 0 ;
	virtual long __cdecl style() = 0 ;
	virtual void __cdecl setEnabled(bool enabled) = 0 ;
	virtual bool __cdecl isEnabled() = 0 ;
};

class PASCALIMPLEMENTATION TUIAlertAction : public Macapi::Objectivec::TOCGenericImport__2<_di_UIAlertActionClass,_di_UIAlertAction>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UIAlertActionClass,_di_UIAlertAction> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUIAlertAction(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UIAlertActionClass,_di_UIAlertAction>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUIAlertAction() { }
	
};


__interface  INTERFACE_UUID("{7713141B-587B-4072-A11E-8EC194701211}") UIAlertControllerClass  : public UIViewControllerClass 
{
	virtual void * __cdecl alertControllerWithTitle(Iosapi::Foundation::_di_NSString title, Iosapi::Foundation::_di_NSString message, long preferredStyle) = 0 ;
};

__interface  INTERFACE_UUID("{A3DCFD49-6EF7-49FB-97A5-0282DB6AF393}") UIAlertController  : public UIViewController 
{
	virtual void __cdecl addAction(_di_UIAlertAction action) = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl actions() = 0 ;
	virtual void __cdecl setPreferredAction(_di_UIAlertAction preferredAction) = 0 ;
	virtual _di_UIAlertAction __cdecl preferredAction() = 0 ;
	virtual void __cdecl addTextFieldWithConfigurationHandler(TUIKitConfigurationHandler configurationHandler) = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl textFields() = 0 ;
	HIDESBASE virtual void __cdecl setTitle(Iosapi::Foundation::_di_NSString title) = 0 ;
	HIDESBASE virtual Iosapi::Foundation::_di_NSString __cdecl title() = 0 ;
	virtual void __cdecl setMessage(Iosapi::Foundation::_di_NSString message) = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl message() = 0 ;
	virtual long __cdecl preferredStyle() = 0 ;
};

class PASCALIMPLEMENTATION TUIAlertController : public Macapi::Objectivec::TOCGenericImport__2<_di_UIAlertControllerClass,_di_UIAlertController>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UIAlertControllerClass,_di_UIAlertController> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUIAlertController(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UIAlertControllerClass,_di_UIAlertController>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUIAlertController() { }
	
};


//-- var, const, procedure ---------------------------------------------------
#define libUIKit u"/System/Library/Frameworks/UIKit.framework/UIKit"
extern "C" UIEdgeInsets __cdecl UIEdgeInsetsMake(double top, double left, double bottom, double right);
extern "C" Iosapi::Foundation::NSRect __cdecl UIEdgeInsetsInsetRect(Iosapi::Foundation::NSRect rect, UIEdgeInsets insets);
extern "C" UIOffset __cdecl UIOffsetMake(double horizontal, double vertical);
extern "C" bool __cdecl UIEdgeInsetsEqualToEdgeInsets(UIEdgeInsets insets1, UIEdgeInsets insets2);
extern "C" bool __cdecl UIOffsetEqualToOffset(UIOffset offset1, UIOffset offset2);
extern "C" void * __cdecl NSStringFromCGPoint(Iosapi::Foundation::NSPoint point);
extern "C" void * __cdecl NSStringFromCGVector(Iosapi::Coregraphics::CGVector vector);
extern "C" void * __cdecl NSStringFromCGSize(Iosapi::Foundation::NSSize size);
extern "C" void * __cdecl NSStringFromCGRect(Iosapi::Foundation::NSRect rect);
extern "C" void * __cdecl NSStringFromCGAffineTransform(Iosapi::Coregraphics::CGAffineTransform transform);
extern "C" void * __cdecl NSStringFromUIEdgeInsets(UIEdgeInsets insets);
extern "C" void * __cdecl NSStringFromUIOffset(UIOffset offset);
extern "C" Iosapi::Foundation::NSPoint __cdecl CGPointFromString(void * string);
extern "C" Iosapi::Coregraphics::CGVector __cdecl CGVectorFromString(void * string);
extern "C" Iosapi::Foundation::NSSize __cdecl CGSizeFromString(void * string);
extern "C" Iosapi::Foundation::NSRect __cdecl CGRectFromString(void * string);
extern "C" Iosapi::Coregraphics::CGAffineTransform __cdecl CGAffineTransformFromString(void * string);
extern "C" UIEdgeInsets __cdecl UIEdgeInsetsFromString(void * string);
extern "C" UIOffset __cdecl UIOffsetFromString(void * string);
extern DELPHI_PACKAGE void * __cdecl _NSDictionaryOfVariableBindings(void * commaSeparatedKeysString, void * firstValue);
extern "C" System::Byte __cdecl NSTextAlignmentToCTTextAlignment(long NSTextAlignment);
extern "C" long __cdecl NSTextAlignmentFromCTTextAlignment(System::Byte CTTextAlignment);
extern "C" void * __cdecl UIImagePNGRepresentation(void * image);
extern "C" void * __cdecl UIImageJPEGRepresentation(void * image, double compressionQuality);
extern "C" void __cdecl UIAccessibilityZoomFocusChanged(long type, Iosapi::Foundation::NSRect frame, void * view);
extern "C" void __cdecl UIAccessibilityRegisterGestureConflictWithZoom(void);
extern "C" long __cdecl UIGuidedAccessRestrictionStateForIdentifier(void * restrictionIdentifier);
extern "C" Iosapi::Foundation::NSRect __cdecl UIAccessibilityConvertFrameToScreenCoordinates(Iosapi::Foundation::NSRect rect, void * view);
extern "C" void * __cdecl UIAccessibilityConvertPathToScreenCoordinates(void * path, void * view);
extern "C" void __cdecl UIAccessibilityPostNotification(unsigned notification, void * argument);
extern "C" bool __cdecl UIAccessibilityIsVoiceOverRunning(void);
extern "C" bool __cdecl UIAccessibilityIsMonoAudioEnabled(void);
extern "C" bool __cdecl UIAccessibilityIsClosedCaptioningEnabled(void);
extern "C" bool __cdecl UIAccessibilityIsInvertColorsEnabled(void);
extern "C" bool __cdecl UIAccessibilityIsGuidedAccessEnabled(void);
extern "C" bool __cdecl UIAccessibilityIsBoldTextEnabled(void);
extern "C" bool __cdecl UIAccessibilityIsGrayscaleEnabled(void);
extern "C" bool __cdecl UIAccessibilityIsReduceTransparencyEnabled(void);
extern "C" bool __cdecl UIAccessibilityIsReduceMotionEnabled(void);
extern "C" bool __cdecl UIAccessibilityDarkerSystemColorsEnabled(void);
extern "C" bool __cdecl UIAccessibilityIsSwitchControlRunning(void);
extern "C" bool __cdecl UIAccessibilityIsSpeakSelectionEnabled(void);
extern "C" bool __cdecl UIAccessibilityIsSpeakScreenEnabled(void);
extern "C" void __cdecl UIAccessibilityRequestGuidedAccessSession(bool enable, TUIKitCompletion completionHandler);
extern "C" void * __cdecl UIGraphicsGetCurrentContext(void);
extern "C" void __cdecl UIGraphicsPushContext(void * context);
extern "C" void __cdecl UIGraphicsPopContext(void);
extern "C" void __cdecl UIRectFillUsingBlendMode(Iosapi::Foundation::NSRect rect, unsigned blendMode);
extern "C" void __cdecl UIRectFill(Iosapi::Foundation::NSRect rect);
extern "C" void __cdecl UIRectFrameUsingBlendMode(Iosapi::Foundation::NSRect rect, unsigned blendMode);
extern "C" void __cdecl UIRectFrame(Iosapi::Foundation::NSRect rect);
extern "C" void __cdecl UIRectClip(Iosapi::Foundation::NSRect rect);
extern "C" void __cdecl UIGraphicsBeginImageContext(Iosapi::Foundation::NSSize size);
extern "C" void __cdecl UIGraphicsBeginImageContextWithOptions(Iosapi::Foundation::NSSize size, bool opaque, double scale);
extern "C" void * __cdecl UIGraphicsGetImageFromCurrentImageContext(void);
extern "C" void __cdecl UIGraphicsEndImageContext(void);
extern "C" bool __cdecl UIGraphicsBeginPDFContextToFile(void * path, Iosapi::Foundation::NSRect bounds, void * documentInfo);
extern "C" void __cdecl UIGraphicsBeginPDFContextToData(void * data, Iosapi::Foundation::NSRect bounds, void * documentInfo);
extern "C" void __cdecl UIGraphicsEndPDFContext(void);
extern "C" void __cdecl UIGraphicsBeginPDFPage(void);
extern "C" void __cdecl UIGraphicsBeginPDFPageWithInfo(Iosapi::Foundation::NSRect bounds, void * pageInfo);
extern "C" Iosapi::Foundation::NSRect __cdecl UIGraphicsGetPDFContextBounds(void);
extern "C" void __cdecl UIGraphicsSetPDFContextURLForRect(void * url, Iosapi::Foundation::NSRect rect);
extern "C" void __cdecl UIGraphicsAddPDFContextDestinationAtPoint(void * name, Iosapi::Foundation::NSPoint point);
extern "C" void __cdecl UIGraphicsSetPDFContextDestinationForRect(void * name, Iosapi::Foundation::NSRect rect);
extern "C" void __cdecl UIImageWriteToSavedPhotosAlbum(void * image, void * completionTarget, void * completionSelector, void * contextInfo);
extern "C" bool __cdecl UIVideoAtPathIsCompatibleWithSavedPhotosAlbum(void * videoPath);
extern "C" void __cdecl UISaveVideoAtPathToSavedPhotosAlbum(void * videoPath, void * completionTarget, void * completionSelector, void * contextInfo);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall NSFontAttributeName(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall NSParagraphStyleAttributeName(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall NSForegroundColorAttributeName(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall NSBackgroundColorAttributeName(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall NSLigatureAttributeName(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall NSKernAttributeName(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall NSStrikethroughStyleAttributeName(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall NSUnderlineStyleAttributeName(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall NSStrokeColorAttributeName(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall NSStrokeWidthAttributeName(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall NSShadowAttributeName(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall NSTextEffectAttributeName(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall NSAttachmentAttributeName(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall NSLinkAttributeName(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall NSBaselineOffsetAttributeName(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall NSUnderlineColorAttributeName(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall NSStrikethroughColorAttributeName(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall NSObliquenessAttributeName(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall NSExpansionAttributeName(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall NSWritingDirectionAttributeName(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall NSVerticalGlyphFormAttributeName(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall NSTextEffectLetterpressStyle(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall NSPlainTextDocumentType(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall NSRTFTextDocumentType(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall NSRTFDTextDocumentType(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall NSHTMLTextDocumentType(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall NSTextLayoutSectionOrientation(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall NSTextLayoutSectionRange(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall NSDocumentTypeDocumentAttribute(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall NSCharacterEncodingDocumentAttribute(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall NSDefaultAttributesDocumentAttribute(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall NSPaperSizeDocumentAttribute(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall NSPaperMarginDocumentAttribute(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall NSViewSizeDocumentAttribute(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall NSViewZoomDocumentAttribute(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall NSViewModeDocumentAttribute(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall NSReadOnlyDocumentAttribute(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall NSBackgroundColorDocumentAttribute(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall NSHyphenationFactorDocumentAttribute(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall NSDefaultTabIntervalDocumentAttribute(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall NSTextLayoutSectionsAttribute(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall NSTextStorageWillProcessEditingNotification(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall NSTextStorageDidProcessEditingNotification(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIFontDescriptorFamilyAttribute(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIFontDescriptorNameAttribute(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIFontDescriptorFaceAttribute(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIFontDescriptorSizeAttribute(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIFontDescriptorVisibleNameAttribute(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIFontDescriptorMatrixAttribute(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIFontDescriptorCharacterSetAttribute(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIFontDescriptorCascadeListAttribute(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIFontDescriptorTraitsAttribute(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIFontDescriptorFixedAdvanceAttribute(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIFontDescriptorFeatureSettingsAttribute(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIFontDescriptorTextStyleAttribute(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIFontSymbolicTrait(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIFontWeightTrait(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIFontWidthTrait(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIFontSlantTrait(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIFontFeatureTypeIdentifierKey(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIFontFeatureSelectorIdentifierKey(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIFontTextStyleHeadline(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIFontTextStyleBody(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIFontTextStyleSubheadline(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIFontTextStyleFootnote(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIFontTextStyleCaption1(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIFontTextStyleCaption2(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall NSTabColumnTerminatorsAttributeName(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIKeyInputUpArrow(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIKeyInputDownArrow(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIKeyInputLeftArrow(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIKeyInputRightArrow(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIKeyInputEscape(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UITextAttributeFont(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UITextAttributeTextColor(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UITextAttributeTextShadowColor(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UITextAttributeTextShadowOffset(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UITableViewIndexSearch(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UITableViewSelectionDidChangeNotification(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIAccessibilityAnnouncementDidFinishNotification(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIAccessibilityAnnouncementKeyStringValue(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIAccessibilityAnnouncementKeyWasSuccessful(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIAccessibilitySpeechAttributePunctuation(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIAccessibilitySpeechAttributeLanguage(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIAccessibilitySpeechAttributePitch(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIAccessibilityVoiceOverStatusChanged(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIAccessibilityMonoAudioStatusDidChangeNotification(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIAccessibilityClosedCaptioningStatusDidChangeNotification(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIAccessibilityInvertColorsStatusDidChangeNotification(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIAccessibilityGuidedAccessStatusDidChangeNotification(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UITextInputTextBackgroundColorKey(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UITextInputTextColorKey(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UITextInputTextFontKey(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UITextInputCurrentInputModeDidChangeNotification(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UITextFieldTextDidBeginEditingNotification(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UITextFieldTextDidEndEditingNotification(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UITextFieldTextDidChangeNotification(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIActivityTypePostToFacebook(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIActivityTypePostToTwitter(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIActivityTypePostToWeibo(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIActivityTypeMessage(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIActivityTypeMail(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIActivityTypePrint(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIActivityTypeCopyToPasteboard(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIActivityTypeAssignToContact(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIActivityTypeSaveToCameraRoll(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIActivityTypeAddToReadingList(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIActivityTypePostToFlickr(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIActivityTypePostToVimeo(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIActivityTypePostToTencentWeibo(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIActivityTypeAirDrop(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIDeviceOrientationDidChangeNotification(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIDeviceBatteryStateDidChangeNotification(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIDeviceBatteryLevelDidChangeNotification(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIDeviceProximityStateDidChangeNotification(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIApplicationInvalidInterfaceOrientationException(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UITrackingRunLoopMode(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIApplicationDidEnterBackgroundNotification(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIApplicationWillEnterForegroundNotification(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIApplicationDidFinishLaunchingNotification(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIApplicationDidBecomeActiveNotification(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIApplicationWillResignActiveNotification(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIApplicationDidReceiveMemoryWarningNotification(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIApplicationWillTerminateNotification(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIApplicationSignificantTimeChangeNotification(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIApplicationWillChangeStatusBarOrientationNotification(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIApplicationDidChangeStatusBarOrientationNotification(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIApplicationStatusBarOrientationUserInfoKey(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIApplicationWillChangeStatusBarFrameNotification(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIApplicationDidChangeStatusBarFrameNotification(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIApplicationStatusBarFrameUserInfoKey(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIApplicationBackgroundRefreshStatusDidChangeNotification(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIApplicationLaunchOptionsURLKey(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIApplicationLaunchOptionsSourceApplicationKey(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIApplicationLaunchOptionsRemoteNotificationKey(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIApplicationLaunchOptionsLocalNotificationKey(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIApplicationLaunchOptionsAnnotationKey(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIApplicationProtectedDataWillBecomeUnavailable(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIApplicationProtectedDataDidBecomeAvailable(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIApplicationLaunchOptionsLocationKey(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIApplicationLaunchOptionsNewsstandDownloadsKey(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIApplicationLaunchOptionsBluetoothCentralsKey(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIApplicationLaunchOptionsBluetoothPeripheralsKey(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIContentSizeCategoryExtraSmall(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIContentSizeCategorySmall(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIContentSizeCategoryMedium(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIContentSizeCategoryLarge(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIContentSizeCategoryExtraLarge(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIContentSizeCategoryExtraExtraLarge(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIContentSizeCategoryExtraExtraExtraLarge(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIContentSizeCategoryAccessibilityMedium(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIContentSizeCategoryAccessibilityLarge(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIContentSizeCategoryAccessibilityExtraLarge(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIContentSizeCategoryAccessibilityExtraExtraLarge(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIContentSizeCategoryAccessibilityExtraExtraExtraLarge(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIContentSizeCategoryDidChangeNotification(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIContentSizeCategoryNewValueKey(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIApplicationUserDidTakeScreenshotNotification(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIStateRestorationViewControllerStoryboardKey(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIApplicationStateRestorationBundleVersionKey(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIApplicationStateRestorationUserInterfaceIdiomKey(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIApplicationStateRestorationTimestampKey(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIApplicationStateRestorationSystemVersionKey(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIViewControllerHierarchyInconsistencyException(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UICollectionElementKindSectionHeader(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UICollectionElementKindSectionFooter(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIDocumentStateChangedNotification(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIImagePickerControllerMediaType(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIImagePickerControllerOriginalImage(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIImagePickerControllerEditedImage(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIImagePickerControllerCropRect(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIImagePickerControllerMediaURL(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIImagePickerControllerReferenceURL(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIImagePickerControllerMediaMetadata(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UILocalNotificationDefaultSoundName(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIMenuControllerWillShowMenuNotification(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIMenuControllerDidShowMenuNotification(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIMenuControllerWillHideMenuNotification(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIMenuControllerDidHideMenuNotification(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIMenuControllerMenuFrameDidChangeNotification(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UINibExternalObjects(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UINibProxiedObjectsKey(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIPageViewControllerOptionSpineLocationKey(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIPageViewControllerOptionInterPageSpacingKey(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIPasteboardNameGeneral(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIPasteboardNameFind(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIPasteboardChangedNotification(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIPasteboardChangedTypesAddedKey(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIPasteboardChangedTypesRemovedKey(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIPasteboardRemovedNotification(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIPrintErrorDomain(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIScreenDidConnectNotification(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIScreenDidDisconnectNotification(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIScreenModeDidChangeNotification(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIScreenBrightnessDidChangeNotification(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UITransitionContextFromViewControllerKey(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UITransitionContextToViewControllerKey(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UITextViewTextDidBeginEditingNotification(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UITextViewTextDidChangeNotification(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UITextViewTextDidEndEditingNotification(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIWindowDidBecomeVisibleNotification(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIWindowDidBecomeHiddenNotification(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIWindowDidBecomeKeyNotification(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIWindowDidResignKeyNotification(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIKeyboardWillShowNotification(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIKeyboardDidShowNotification(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIKeyboardWillHideNotification(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIKeyboardDidHideNotification(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIKeyboardFrameBeginUserInfoKey(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIKeyboardFrameEndUserInfoKey(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIKeyboardAnimationDurationUserInfoKey(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIKeyboardAnimationCurveUserInfoKey(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIKeyboardWillChangeFrameNotification(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIKeyboardDidChangeFrameNotification(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIKeyboardCenterBeginUserInfoKey(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIKeyboardCenterEndUserInfoKey(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall UIKeyboardBoundsUserInfoKey(void);
}	/* namespace Uikit */
}	/* namespace Iosapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IOSAPI_UIKIT)
using namespace Iosapi::Uikit;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IOSAPI)
using namespace Iosapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Iosapi_UikitHPP
