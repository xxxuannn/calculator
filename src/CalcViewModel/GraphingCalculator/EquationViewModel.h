// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#pragma once

#include "../Common/Utils.h"

namespace GraphControl
{
    ref class Equation;
    ref class KeyGraphFeaturesInfo;
}

namespace CalculatorApp::ViewModel
{
public
    ref class GridDisplayItems sealed : public Windows::UI::Xaml::Data::INotifyPropertyChanged
    {
    public:
        GridDisplayItems();

        OBSERVABLE_OBJECT();
        OBSERVABLE_PROPERTY_RW(Platform::String ^, Expression);
        OBSERVABLE_PROPERTY_RW(Platform::String ^, Direction);
    };

public
    ref class KeyGraphFeaturesItem sealed : public Windows::UI::Xaml::Data::INotifyPropertyChanged
    {
    public:
        KeyGraphFeaturesItem();

        OBSERVABLE_OBJECT();
        OBSERVABLE_PROPERTY_RW(Platform::String ^, Title);
        OBSERVABLE_PROPERTY_RW(Windows::Foundation::Collections::IObservableVector<Platform::String ^> ^, DisplayItems);
        OBSERVABLE_PROPERTY_RW(Windows::Foundation::Collections::IObservableVector<GridDisplayItems ^> ^, GridItems);
        OBSERVABLE_PROPERTY_RW(bool, IsText);
    };

public
    ref class EquationViewModel sealed : public Windows::UI::Xaml::Data::INotifyPropertyChanged
    {
    public:
        EquationViewModel(GraphControl::Equation ^ equation, int functionLabelIndex, Windows::UI::Color color, int colorIndex);

        OBSERVABLE_OBJECT();
        OBSERVABLE_PROPERTY_R(GraphControl::Equation ^, GraphEquation);
        OBSERVABLE_PROPERTY_RW(int, FunctionLabelIndex);
        OBSERVABLE_PROPERTY_RW(bool, IsLastItemInList);
        PROPERTY_RW(int, LineColorIndex);

        property Platform::String ^ Expression
        {
            Platform::String ^ get()
            {
                return GraphEquation->Expression;
            }
            void set(Platform::String ^ value)
            {
                if (GraphEquation->Expression != value)
                {
                    GraphEquation->Expression = value;
                    RaisePropertyChanged("Expression");
                }
            }
        }

        property Windows::UI::Color LineColor
        {
            Windows::UI::Color get()
            {
                return GraphEquation->LineColor;
            }
            void set(Windows::UI::Color value)
            {
                if (!Utils::AreColorsEqual(GraphEquation->LineColor, value))
                {
                    GraphEquation->LineColor = value;
                    RaisePropertyChanged("LineColor");
                }
            }
        }

        property bool IsLineEnabled
        {
            bool get()
            {
                return GraphEquation->IsLineEnabled;
            }
            void set(bool value)
            {
                if (GraphEquation->IsLineEnabled != value)
                {
                    GraphEquation->IsLineEnabled = value;
                    RaisePropertyChanged("IsLineEnabled");
                }
            }
        }

        // Key Graph Features
        OBSERVABLE_PROPERTY_R(Platform::String ^, AnalysisErrorString);
        OBSERVABLE_PROPERTY_R(bool, AnalysisErrorVisible);
        OBSERVABLE_PROPERTY_R(Windows::Foundation::Collections::IObservableVector<CalculatorApp::ViewModel::KeyGraphFeaturesItem ^> ^, KeyGraphFeaturesItems)

        void PopulateKeyGraphFeatures(GraphControl::KeyGraphFeaturesInfo ^ info);

        static Platform::String ^ EquationErrorText(GraphControl::ErrorType errorType, int errorCode);

    private:
        void AddKeyGraphFeature(Platform::String ^ title, Platform::String ^ expression, Platform::String ^ errorString);
        void AddKeyGraphFeature(
            Platform::String ^ title,
            Windows::Foundation::Collections::IVector<Platform::String ^> ^ expressionVector,
            Platform::String ^ errorString);
        void AddParityKeyGraphFeature(GraphControl::KeyGraphFeaturesInfo ^ info);
        void AddPeriodicityKeyGraphFeature(GraphControl::KeyGraphFeaturesInfo ^ info);
        void AddMonotoncityKeyGraphFeature(GraphControl::KeyGraphFeaturesInfo ^ info);
        void AddTooComplexKeyGraphFeature(GraphControl::KeyGraphFeaturesInfo ^ info);

        Windows::Foundation::Collections::IObservableMap<Platform::String ^, Platform::String ^> ^ m_Monotonicity;
        Windows::ApplicationModel::Resources::ResourceLoader ^ m_resourceLoader;
    };

    class EvaluationErrorCode
    {
    private:
        String s = L"GeneralError";

    public:
        set_S()
        {
            return s;
        }
    };

    class Overflow : public EvaluationErrorCode
    {
    private:
        String s = L"Overflow";
    };

    class RequireRadiansMode : public EvaluationErrorCode
    {
    private:
        String s = L"RequireRadiansMode";
    };

    class RequireDegreesMode : public EvaluationErrorCode
    {
    private:
        String s = L"RequireDegreesMode";
    };

    class FactorialInvalidArgument : public EvaluationErrorCode
    {
    private:
        String s = L"FactorialInvalidArgument";
    };

    class Factorial2InvalidArgument : public EvaluationErrorCode
    {
    private:
        String s = L"FactorialInvalidArgument";
    };

    class FactorialCannotPerformOnLargeNumber : public EvaluationErrorCode
    {
    private:
        String s = L"FactorialCannotPerformOnLargeNumber";
    };

    class ModuloCannotPerformOnFloat : public EvaluationErrorCode
    {
    private:
        String s = L"ModuloCannotPerformOnFloat";
    };

    class TooComplexToSolve : public EvaluationErrorCode
    {
    private:
        String s = L"TooComplexToSolve";
    };

    class EquationTooComplexToSolve : public EvaluationErrorCode
    {
    private:
        String s = L"TooComplexToSolve";
    };

    class EquationTooComplexToSolveSymbolic : public EvaluationErrorCode
    {
    private:
        String s = L"TooComplexToSolve";
    };

    class EquationTooComplexToPlot : public EvaluationErrorCode
    {
    private:
        String s = L"TooComplexToSolve";
    };

    class InequalityTooComplexToSolve : public EvaluationErrorCode
    {
    private:
        String s = L"TooComplexToSolve";
    };

    class GE_TooComplexToSolve : public EvaluationErrorCode
    {
    private:
        String s = L"TooComplexToSolve";
    };

    class EquationHasNoSolution : public EvaluationErrorCode
    {
    private:
        String s = L"EquationHasNoSolution";
    };

    class InequalityHasNoSolution : public EvaluationErrorCode
    {
    private:
        String s = L"EquationHasNoSolution";
    };

    class DivideByZero : public EvaluationErrorCode
    {
    private:
        String s = L"DivideByZero";
    };

    class MutuallyExclusiveConditions : public EvaluationErrorCode
    {
    private:
        String s = L"MutuallyExclusiveConditions";
    };

    class OutOfDomain : public EvaluationErrorCode
    {
    private:
        String s = L"OutOfDomain";
    };

    class GE_NotSupported : public EvaluationErrorCode
    {
    private:
        String s = L"GE_NotSupported";
    };

    class SyntaxErrorCode
    {
    private:
        String s = L"GeneralError";

    public:
        set_S()
        {
            return s;
        }
    };

    class ParenthesisMismatch : public SyntaxErrorCode
    {
    private:
        String s = L"ParenthesisMismatch";
    };
    class UnmatchedParenthesis : public SyntaxErrorCode
    {
    private:
        String s = L"UnmatchedParenthesis";
    };
    class TooManyDecimalPoints : public SyntaxErrorCode
    {
    private:
        String s = L"TooManyDecimalPoints";
    };
    class DecimalPointWithoutDigits : public SyntaxErrorCode
    {
    private:
        String s = L"DecimalPointWithoutDigits";
    };
    class UnexpectedEndOfExpression : public SyntaxErrorCode
    {
    private:
        String s = L"UnexpectedEndOfExpression";
    };
    class UnexpectedToken : public SyntaxErrorCode
    {
    private:
        String s = L"UnexpectedToken";
    };
    class InvalidToken : public SyntaxErrorCode
    {
    private:
        String s = L"InvalidToken";
    };
    class TooManyEquals : public SyntaxErrorCode
    {
    private:
        String s = L"TooManyEquals";
    };
    class EqualWithoutGraphVariable : public SyntaxErrorCode
    {
    private:
        String s = L"EqualWithoutGraphVariable";
    };
    class InvalidEquationSyntax : public SyntaxErrorCode
    {
    private:
        String s = L"InvalidEquationSyntax";
    };
    class InvalidEquationFormat : public SyntaxErrorCode
    {
    private:
        String s = L"InvalidEquationSyntax";
    };
    class EmptyExpression : public SyntaxErrorCode
    {
    private:
        String s = L"EmptyExpression";
    };
    class EqualWithoutEquation : public SyntaxErrorCode
    {
    private:
        String s = L"EqualWithoutEquation";
    };
    class ExpectParenthesisAfterFunctionName : public SyntaxErrorCode
    {
    private:
        String s = L"ExpectParenthesisAfterFunctionName";
    };
    class IncorrectNumParameter : public SyntaxErrorCode
    {
    private:
        String s = L"IncorrectNumParameter";
    };
    class InvalidVariableNameFormat : public SyntaxErrorCode
    {
    private:
        String s = L"InvalidVariableNameFormat";
    };
    class BracketMismatch : public SyntaxErrorCode
    {
    private:
        String s = L"BracketMismatch";
    };
    class UnmatchedBracket : public SyntaxErrorCode
    {
    private:
        String s = L"UnmatchedBracket";
    };
    class CannotUseIInReal : public SyntaxErrorCode
    {
    private:
        String s = L"CannotUseIInReal";
    };
    class InvalidNumberDigit : public SyntaxErrorCode
    {
    private:
        String s = L"InvalidNumberDigit";
    };
    class InvalidNumberBase : public SyntaxErrorCode
    {
    private:
        String s = L"InvalidNumberBase";
    };
    class InvalidVariableSpecification : public SyntaxErrorCode
    {
    private:
        String s = L"InvalidVariableSpecification";
    };
    class ExpectingLogicalOperands : public SyntaxErrorCode
    {
    private:
        String s = L"ExpectingLogicalOperands";
    };
    class ExpectingScalarOperands : public SyntaxErrorCode
    {
    private:
        String s = L"ExpectingLogicalOperands";
    };
    class CannotUseIndexVarInOpLimits : public SyntaxErrorCode
    {
    private:
        String s = L"CannotUseIndexVarInOpLimits";
    };
    class CannotUseIndexVarInLimPoint : public SyntaxErrorCode
    {
    private:
        String s = L"Overflow";
    };
    class CannotUseComplexInfinityInReal : public SyntaxErrorCode
    {
    private:
        String s = L"CannotUseComplexInfinityInReal";
    };
    class CannotUseIInInequalitySolving : public SyntaxErrorCode
    {
    private:
        String s = L"CannotUseIInInequalitySolving";
    };

}
