#ifndef LAYERSTYLEWIDGET_H
#define LAYERSTYLEWIDGET_H

#include "QWidget"
#include "QGroupBox"
#include "QHBoxLayout"
#include "QDialog"
#include "sphstyle.h"
#include "gradientcombobox.h"
#include "uilayer.h"
#include "layerparameters.h"
#include "QToolButton"
#include "QCheckBox"
#include "linestylecombobox.h"
#include "fillstylecombobox.h"
#include "colorwheel.h"
#include "QScrollArea"
#include "QToolBox"
#include "QSpacerItem"
#include "labeledwidget.h"
#include "QDoubleSpinBox"
#include "spoilerwidget.h"


class FillStyleWidget : public QWidget
{
        Q_OBJECT;
public:

    SPHStyle * m_Style;
    UILayer *  m_Layer;
    SPHFillStyle * m_FillStyle;

    FillStyleComboBox * PFCombo;
    QSlider * PFSize;
    QSlider * PFSeperation;
    QSlider * PFAngle;
    ColorWheel * PFColor1;
    ColorWheel  * PFColor2;


    QComboBox * m_POColor1Attrib;
    QComboBox * m_POColor2Attrib;
    GradientComboBox * m_POlabelGradientV1;
    GradientComboBox * m_POlabelGradientV2;

    QList<QString> attribs;

    inline FillStyleWidget(UILayer * l,SPHFillStyle * fillstyle, QWidget * parent = nullptr) : QWidget(parent)
    {
        m_Layer = l;
        m_Style = l->GetStyleRef();
        m_FillStyle = fillstyle;

        QVBoxLayout * wl = new QVBoxLayout();
        setLayout(wl);

        FillStyleComboBox * m_labellstyle = new FillStyleComboBox();
        m_labellstyle->SetCurrentFillStyle(*m_FillStyle);
        connect(m_labellstyle,SIGNAL(OnGradientChanged()),this,SLOT(OnPolygonFSClicked()));
        wl->addWidget(m_labellstyle);

        PFCombo = m_labellstyle ;

        PFSize= new QSlider();
        PFSize->setMaximum(50);
        PFSize->setMinimum(1);
        PFSize->setValue(m_FillStyle->m_LineSize);
        PFSize->setOrientation(Qt::Horizontal);
        PFSeperation= new QSlider();
        PFSeperation->setMaximum(50);
        PFSeperation->setMinimum(1);
        PFSeperation->setValue(m_FillStyle->m_LineSeperation);
        PFSeperation->setOrientation(Qt::Horizontal);
        PFAngle= new QSlider();
        PFAngle->setMaximum(180);
        PFAngle->setMinimum(0);
        PFAngle->setValue(m_FillStyle->m_LineAngle);
        PFAngle->setOrientation(Qt::Horizontal);
        PFColor1 = new ColorWheel();
        PFColor1->setMaximumSize(150,150);
        PFColor1->setColor(m_FillStyle->m_Color1.ToQColor());
        PFColor2 = new ColorWheel();
        PFColor2->setMaximumSize(150,150);
        PFColor2->setColor(m_FillStyle->m_Color1.ToQColor());

        connect(PFSize, SIGNAL(valueChanged(int)), this, SLOT(OnPolygonFSSized(int)));
        connect(PFSeperation, SIGNAL(valueChanged(int)), this, SLOT(OnPolygonFSSeperation(int)));
        connect(PFAngle, SIGNAL(valueChanged(int)), this, SLOT(OnPolygonFSAngle(int)));
        connect(PFColor1,SIGNAL(colorChange(QColor)),this,SLOT(OnPolygonFSColor1(QColor)));
        connect(PFColor2,SIGNAL(colorChange(QColor)),this,SLOT(OnPolygonFSColor2(QColor)));

        wl->addWidget(new QVLabeledWidget("Lines Size",PFSize));
        wl->addWidget(new QVLabeledWidget("Lines Seperation",PFSeperation));
        wl->addWidget(new QVLabeledWidget("Lines Angle",PFAngle));

        wl->addWidget(new QVLabeledWidget("Primary Color",PFColor1));
        wl->addWidget(new QVLabeledWidget("Secundary Color",PFColor2));


        attribs = m_Layer->GetAllAttributes();

        attribs.prepend("<none>");
        m_POColor1Attrib = new QComboBox();
        m_POColor2Attrib = new QComboBox();

        m_POColor1Attrib->addItems(attribs);
        m_POColor2Attrib->addItems(attribs);

        if(attribs.contains(m_FillStyle->m_Color1Parameter))
        {
            m_POColor1Attrib->setCurrentIndex(attribs.indexOf(m_FillStyle->m_Color1Parameter));
        }
        if(attribs.contains(m_FillStyle->m_Color2Parameter))
        {
            m_POColor2Attrib->setCurrentIndex(attribs.indexOf(m_FillStyle->m_Color2Parameter));
        }

        connect(m_POColor1Attrib,SIGNAL(currentIndexChanged(int)),this,SLOT(OnAttrib1(int)));
        connect(m_POColor2Attrib,SIGNAL(currentIndexChanged(int)),this,SLOT(OnAttrib2(int)));

        m_POlabelGradientV1  = new GradientComboBox();
        m_POlabelGradientV1->SetCurrentGradient(m_FillStyle->m_ColorGradient1);
        connect(m_POlabelGradientV1,SIGNAL(OnGradientChanged()),this,SLOT(OnGradientClickedsb1()));

        m_POlabelGradientV2 = new GradientComboBox();
        m_POlabelGradientV2->SetCurrentGradient(m_FillStyle->m_ColorGradient2);
        connect(m_POlabelGradientV2,SIGNAL(OnGradientChanged()),this,SLOT(OnGradientClickedsb2()));

        wl->addWidget(new QVLabeledWidget("Color 1 From Attribute",m_POColor1Attrib));
        wl->addWidget(new QVLabeledWidget("Color 1 Gradient",m_POlabelGradientV1));
        wl->addWidget(new QVLabeledWidget("Color 2 From Attribute",m_POColor2Attrib));
        wl->addWidget(new QVLabeledWidget("Color 2 Gradient",m_POlabelGradientV2));
    }
public slots:

    inline void OnGradientClickedsb1()
    {
        m_FillStyle->m_ColorGradient1 = m_POlabelGradientV1->GetCurrentGradient();
    }

    inline void OnGradientClickedsb2()
    {
        m_FillStyle->m_ColorGradient2 = m_POlabelGradientV2->GetCurrentGradient();
    }

    inline void OnAttrib1(int x)
    {

        if(x > 0)
        {
            m_FillStyle->m_Color1Parameter = attribs.at(x);
        }else
        {
            m_FillStyle->m_Color1Parameter = "";
        }
    }

    inline void OnAttrib2(int x)
    {
        if(x > 0)
        {
            m_FillStyle->m_Color1Parameter = attribs.at(x);
        }else
        {
            m_FillStyle->m_Color2Parameter = "";
        }

    }

    //POLYGON FILL STYLE
    inline void OnPolygonFSClicked()
    {

        (*m_FillStyle) = PFCombo->GetCurrentGradient();
        PFSize->setValue(m_FillStyle->m_LineSize);
        PFAngle->setValue(m_FillStyle->m_LineAngle);
        PFSeperation->setValue(m_FillStyle->m_LineSeperation);
        PFColor1->setColor(m_FillStyle->m_Color1.ToQColor());
        PFColor2->setColor(m_FillStyle->m_Color2.ToQColor());
    }


    inline void OnPolygonFSSized(int v)
    {
        m_FillStyle->m_LineSize = v;

        PFCombo->SetCurrentFillStyle(*m_FillStyle);
        PFCombo->update();
    }


    inline void OnPolygonFSSeperation(int v)
    {
        m_FillStyle->m_LineSeperation = v;
        PFCombo->SetCurrentFillStyle(*m_FillStyle);
        PFCombo->update();
    }

    inline void OnPolygonFSAngle(int v)
    {
        m_FillStyle->m_LineAngle = v;
        PFCombo->SetCurrentFillStyle(*m_FillStyle);
        PFCombo->update();
    }

    inline void OnPolygonFSColor1(QColor c)
    {
        m_FillStyle->m_Color1.FromQColor(c);
        PFCombo->SetCurrentFillStyle(*m_FillStyle);
        PFCombo->update();
    }

    inline void OnPolygonFSColor2(QColor c)
    {
        m_FillStyle->m_Color2.FromQColor(c);
        PFCombo->SetCurrentFillStyle(m_Style->m_PolygonFillStyle);
        PFCombo->update();
    }


};


class LineStyleWidget : public QWidget
{
        Q_OBJECT;
public:

    SPHStyle * m_Style;
    UILayer *  m_Layer;
    SPHLineStyle * m_LineStyle;

    LineStyleComboBox * PoLCombo;
    QSlider * PoLSizer;
    ColorWheel * PoLColor1;
    ColorWheel  * PoLColor2;

    LineStyleComboBox * PLCombo;
    QSlider * PLSizer;
    ColorWheel * PLColor1;
    ColorWheel  * PLColor2;

    /*QComboBox * m_POColor1Attrib;
    QComboBox * m_POColor2Attrib;
    GradientComboBox * m_POlabelGradientV1;
    GradientComboBox * m_POlabelGradientV2;*/


    inline LineStyleWidget(UILayer * l,SPHLineStyle * linestyle, QWidget * parent = nullptr) : QWidget(parent)
    {

        m_Layer = l;
        m_Style = l->GetStyleRef();
        m_LineStyle = linestyle;

        QVBoxLayout * wl = new QVBoxLayout();
        setLayout(wl);


        LineStyleComboBox * m_labellstyle = new LineStyleComboBox();
        m_labellstyle->SetCurrentLineStyle(*m_LineStyle);
        connect(m_labellstyle,SIGNAL(OnGradientChanged()),this,SLOT(OnPolygonLSClicked()));
        wl->addWidget(m_labellstyle);

        PLCombo = m_labellstyle;

        PLSizer= new QSlider();
        PLSizer->setMaximum(50);
        PLSizer->setMinimum(1);
        PLSizer->setValue(m_LineStyle->m_LineWMax);
        PLSizer->setOrientation(Qt::Horizontal);

        connect(PLSizer, SIGNAL(valueChanged(int)), this, SLOT(OnPolygonLSSized(int)));
        wl->addWidget(new QVLabeledWidget("Line Width",PLSizer));

        PLColor1 = new ColorWheel();
        PLColor1->setMaximumSize(150,150);
        PLColor1->setColor(m_LineStyle->m_Color1.ToQColor());
        wl->addWidget(new QVLabeledWidget("Primary Color",PLColor1));
        PLColor2 = new ColorWheel();
        PLColor2->setMaximumSize(150,150);
        PLColor2->setColor(m_LineStyle->m_Color2.ToQColor());
        wl->addWidget(new QVLabeledWidget("Secundary Color",PLColor2));

        connect(PLColor1,SIGNAL(colorChange(QColor)),this,SLOT(OnPolygonLSColor1(QColor)));
        connect(PLColor2,SIGNAL(colorChange(QColor)),this,SLOT(OnPolygonLSColor2(QColor)));

    }
public slots:

    //POINT LINE STYLE
    inline void OnPolygonLSClicked()
    {

        *m_LineStyle = PLCombo->GetCurrentGradient();
        PLSizer->setValue(m_LineStyle->m_LineWMax);
        PLColor1->setColor(m_LineStyle->m_Color1.ToQColor());
        PLColor2->setColor(m_LineStyle->m_Color2.ToQColor());
    }
    inline void OnPolygonLSSized(int v)
    {

        m_LineStyle->m_LineWMax = v;
        PLCombo->SetCurrentLineStyle(m_Style->m_PolygonLineStyle);
        PLCombo->update();
    }

    inline void OnPolygonLSColor1(QColor c)
    {
        m_LineStyle->m_Color1.FromQColor(c);
        PLCombo->SetCurrentLineStyle(m_Style->m_PolygonLineStyle);
        PLCombo->update();
    }

    inline void OnPolygonLSColor2(QColor c)
    {
        m_LineStyle->m_Color2.FromQColor(c);
        PLCombo->SetCurrentLineStyle(m_Style->m_PolygonLineStyle);
        PLCombo->update();
    }

};

class LayerStyleWidget : public QDialog
{
    Q_OBJECT;

    QVBoxLayout *m_MainLayout;

    QWidget * m_ToolBox;
     SPHStyle * m_Style;
     UILayer *  m_Layer;

     LineStyleComboBox * PLCombo;
     QSlider * PLSizer;
     ColorWheel * PLColor1;
     ColorWheel  * PLColor2;

     FillStyleComboBox * PFCombo;
     QSlider * PFSize;
     QSlider * PFSeperation;
     QSlider * PFAngle;
     ColorWheel * PFColor1;
     ColorWheel  * PFColor2;

     LineStyleComboBox * LLCombo;
     QSlider * LLSizer;
     ColorWheel * LLColor1;
     ColorWheel  * LLColor2;

     LineStyleComboBox * PoLCombo;
     QSlider * PoLSizer;
     ColorWheel * PoLColor1;
     ColorWheel  * PoLColor2;


     FillStyleComboBox * PoFCombo;
     QSlider * PoFSize;
     QSlider * PoSize;
     QSlider * PoFSeperation;
     QSlider * PoFAngle;
     ColorWheel * PoFColor1;
     ColorWheel  * PoFColor2;

     /*QComboBox * m_POColor1Attrib;
     QComboBox * m_POColor2Attrib;
     GradientComboBox * m_POlabelGradientV1;
     GradientComboBox * m_POlabelGradientV2;*/

    QSlider *m_Timeslider = nullptr;

     GradientComboBox * m_labelGradientsb1;
     GradientComboBox * m_labelGradientdb1;
     GradientComboBox * m_labelGradientdb2;

public:
    inline LayerStyleWidget(UILayer * l) : QDialog()
    {
        m_Layer = l;
        m_Style = l->GetStyleRef();

        QString m_Dir = QCoreApplication::applicationDirPath();

        m_MainLayout = new QVBoxLayout();
        this->setLayout(m_MainLayout);


        m_ToolBox = new QWidget();
        m_ToolBox->setMinimumSize(400,600);
        m_ToolBox->setMaximumSize(400,600);

        QScrollArea *scrollArea = new QScrollArea();
        scrollArea->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
        scrollArea->setWidgetResizable( true );
        scrollArea->setGeometry(0,0,500,500);

        m_MainLayout->addWidget(scrollArea);
        QWidget *scrollw = new QWidget();
        scrollArea->setWidget( scrollw );


        QVBoxLayout * m_ToolBoxl = new QVBoxLayout();
        scrollw->setLayout(m_ToolBoxl);

        this->setMinimumSize(400,800);
        {

            QWidget * w = new QWidget();
            QVBoxLayout * wl = new QVBoxLayout();
            w->setLayout(wl);

            QCheckBox * DrawBox = new QCheckBox("Draw this layer");
            QSlider * TransSlider = new QSlider(Qt::Horizontal);

            wl->addWidget(DrawBox);
            wl->addWidget(new QLabeledWidget("Transparancy",TransSlider));

            if(m_Style->m_HasSingleBand)
            {
                //DEM options
                QCheckBox * m_DemBox = new QCheckBox("Is Digital Elevation Model");
                m_DemBox->setChecked(m_Style->m_IsDEM);
                QDoubleSpinBox *m_DemScale = new QDoubleSpinBox();
                m_DemScale->setValue(m_Style->DemScale);
                //HS options
                QCheckBox * m_HSBox = new QCheckBox("Is HillShade");
                m_HSBox->setChecked(m_Style->m_IsHS);
                QDial * m_HSAngle1 = new QDial();
                m_HSAngle1->setWrapping(true);
                m_HSAngle1->setMinimum(0);
                m_HSAngle1->setMaximum(360);
                m_HSAngle1->setValue(m_Style->angle_hor);
                m_HSAngle1->setNotchesVisible(true);
                QSlider * m_HSAngle2 = new QSlider();
                m_HSAngle2->setOrientation(Qt::Horizontal);
                m_HSAngle2->setMinimum(0);
                m_HSAngle2->setMaximum(180);
                m_HSAngle2->setValue(m_Style->angle_vert);

                wl->addWidget(m_DemBox);
                wl->addWidget(new QLabeledWidget("Vertical Scale ",m_DemScale));
                wl->addWidget(m_HSBox);
                wl->addWidget(m_HSAngle1);
                wl->addWidget(m_HSAngle2);

                //connections
                connect(m_DemBox, &QCheckBox::clicked, this, &LayerStyleWidget::OnDemClicked);
                connect(m_HSBox, &QCheckBox::clicked, this, &LayerStyleWidget::OnHSClicked);
                connect(m_DemScale, SIGNAL(valueChanged(double)), this, SLOT(OnDemScaleChanged(double)));
                connect(m_HSAngle1, &QDial::valueChanged, this, &LayerStyleWidget::OnHSAngle1Changed);
                connect(m_HSAngle2, &QSlider::valueChanged, this, &LayerStyleWidget::OnHSAngle2Changed);
            }

            if(m_Style->m_HasDuoBand)
            {
                QCheckBox * m_VelBox = new QCheckBox("Is Velocity");
                connect(m_VelBox, &QCheckBox::clicked, this, &LayerStyleWidget::OnVelocityClicked);

                QSlider * m_VelSpacing = new QSlider();
                m_VelSpacing->setOrientation(Qt::Horizontal);
                m_VelSpacing->setMinimum(0);
                m_VelSpacing->setMaximum(180);
                m_VelSpacing->setValue(m_Style->m_VelSpacing);

                wl->addWidget(m_VelBox);
                wl->addWidget(new QLabeledWidget("Arrow Spacing ",m_VelSpacing));

                connect(m_VelSpacing, &QSlider::valueChanged, this, &LayerStyleWidget::OnVelSpacingChanged);
            }

            //add surface options
            if(m_Style->m_HasSingleBand || m_Style->m_HasDuoBand)
            {
                QCheckBox * m_SurfaceBox = new QCheckBox("Is Surface (seperate surface layer added above the elevation model)");
                m_SurfaceBox->setChecked(m_Style->m_IsSurface);
                connect(m_SurfaceBox, &QCheckBox::clicked, this, &LayerStyleWidget::OnSurfaceClicked);
                QCheckBox * m_SurfaceSecondBox = new QCheckBox("Use second band for height");
                m_SurfaceSecondBox->setChecked(m_Style->m_UseSecondDuoBandAsHeight);
                connect(m_SurfaceSecondBox, &QCheckBox::clicked, this, &LayerStyleWidget::OnSurfaceSecondClicked);
                QCheckBox * m_SurfaceFlowBox = new QCheckBox("Is flow surface");
                m_SurfaceFlowBox->setChecked(m_Style->m_IsSurfaceFlow);
                connect(m_SurfaceFlowBox, &QCheckBox::clicked, this, &LayerStyleWidget::OnSurfaceFlowClicked);

                wl->addWidget(m_SurfaceBox);
                wl->addWidget(m_SurfaceFlowBox);
                wl->addWidget(m_SurfaceSecondBox);
            }

            if(m_Style->m_HasTime)
            {
                QWidget * ButtonWidget = new QWidget();
                QHBoxLayout * ButtonLayout = new QHBoxLayout();
                ButtonWidget->setLayout(ButtonLayout);

                QIcon icon_start;
                QIcon icon_pause;
                QIcon icon_stop;
                icon_start.addFile((m_Dir + SPH_FOLDER_ASSETS + "start1.png"), QSize(), QIcon::Normal, QIcon::Off);
                icon_pause.addFile((m_Dir + SPH_FOLDER_ASSETS + "pause2.png"), QSize(), QIcon::Normal, QIcon::Off);
                icon_stop.addFile((m_Dir + SPH_FOLDER_ASSETS + "stop1.png"), QSize(), QIcon::Normal, QIcon::Off);

                QToolButton * startbutton = new QToolButton();
                startbutton->setIcon(icon_start);
                QToolButton * pausebutton = new QToolButton();
                pausebutton->setIcon(icon_pause);
                QToolButton * stopbutton = new QToolButton();
                stopbutton->setIcon(icon_stop);

                ButtonLayout->addWidget(startbutton);
                ButtonLayout->addWidget(pausebutton);
                ButtonLayout->addWidget(stopbutton);

                connect(startbutton,&QToolButton::pressed,this,&LayerStyleWidget::OnAnimationStart);
                connect(pausebutton,&QToolButton::pressed,this,&LayerStyleWidget::OnAnimationPause);
                connect(stopbutton,&QToolButton::pressed,this,&LayerStyleWidget::OnAnimationStop);

                wl->addWidget(ButtonWidget);

                m_Timeslider = new QSlider();
                m_Timeslider->setMinimum(m_Style->m_TimeMin);
                m_Timeslider->setMaximum(m_Style->m_TimeMax);
                m_Timeslider->setOrientation(Qt::Horizontal);

                connect(m_Timeslider, &QSlider::valueChanged,this,&LayerStyleWidget::TimeChanged);

                QDoubleSpinBox * m_TimeSpeed = new QDoubleSpinBox();
                m_TimeSpeed->setMinimum(0.01);
                m_TimeSpeed->setMaximum(10.0);
                m_TimeSpeed->setDecimals(4);

                m_TimeSpeed->setValue(m_Style->m_PlaySpeed);
                connect(m_TimeSpeed,SIGNAL(valueChanged(double)),this,SLOT(PlaySpeedChanged(double)));

                wl->addWidget(new QLabeledWidget("Time (" + QString::number(m_Style->m_TimeMin) + " - " + QString::number(m_Style->m_TimeMax) + ")",m_Timeslider));
                wl->addWidget(new QLabeledWidget("Speed ",m_TimeSpeed));


            }
            QGroupBox *wbox = new QGroupBox();
            wbox->setTitle("General");
            QVBoxLayout * wboxl = new QVBoxLayout();
            wbox->setLayout(wboxl);
            wboxl->addWidget(w);
            m_ToolBoxl->addWidget(wbox);
        }

        if(m_Style->m_HasSingleBand)
        {
            QWidget * w = new QWidget();
            QVBoxLayout * wl = new QVBoxLayout();
            w->setLayout(wl);

            m_labelGradientsb1 = new GradientComboBox();
            m_labelGradientsb1->SetCurrentGradient(m_Style->m_ColorGradientb1);
            connect(m_labelGradientsb1,SIGNAL(OnGradientChanged()),this,SLOT(OnGradientClickedsb1()));
            wl->addWidget(m_labelGradientsb1);

            QDoubleSpinBox * m_SpinMin;
            QDoubleSpinBox * m_SpinMax;

            m_SpinMax = new QDoubleSpinBox();
            m_SpinMax->setValue(m_Style->m_Intervalb1.GetMax());
            m_SpinMax->setDecimals(6);
            m_SpinMax->setMaximum(1e10);
            m_SpinMax->setMinimum(-1e10);

            m_SpinMin = new QDoubleSpinBox();
            m_SpinMin->setValue(m_Style->m_Intervalb1.GetMin());
            m_SpinMin->setDecimals(6);
            m_SpinMin->setMaximum(1e10);
            m_SpinMin->setMinimum(-1e10);


            QIcon *icon_re = new QIcon();
            icon_re->addFile((m_Dir + SPH_FOLDER_ASSETS + "refresh_24.png"), QSize(), QIcon::Normal, QIcon::Off);
            QToolButton * m_GetMinMaxButton;
            m_GetMinMaxButton = new QToolButton();
            m_GetMinMaxButton->setIcon(*icon_re);
            m_GetMinMaxButton->setIconSize(QSize(22,22));
            m_GetMinMaxButton->resize(22,22);

            wl->addWidget(new QLabeledWidget("Minimum Value",m_SpinMin));
            wl->addWidget(new QLabeledWidget("Maximum Value",m_SpinMax));
            wl->addWidget(new QLabeledWidget("Load Min and Max from Map",m_GetMinMaxButton));

            connect(m_GetMinMaxButton,SIGNAL(pressed()),this,SLOT(OnUpdateMinMax()));
            connect(m_SpinMin, SIGNAL(valueChanged(double)),this,SLOT(OnMinValueChanged(double)));
            connect(m_SpinMax, SIGNAL(valueChanged(double)),this,SLOT(OnMaxValueChanged(double)));

            QGroupBox * gbi = new QGroupBox();
            QVBoxLayout * gbil = new QVBoxLayout();
            gbi->setLayout(gbil);
            gbi->setTitle("Single Band");
            gbil->addWidget(w);

            m_ToolBoxl->addWidget(gbi);
        }
        if(m_Style->m_HasDuoBand)
        {
            QWidget * w = new QWidget();
            QVBoxLayout * wl = new QVBoxLayout();
            w->setLayout(wl);
            wl->addItem(new QSpacerItem(20,600));

            m_labelGradientdb1 = new GradientComboBox();
            m_labelGradientdb1->SetCurrentGradient(m_Style->m_ColorGradientb1);
            connect(m_labelGradientdb1,SIGNAL(OnGradientChanged()),this,SLOT(OnGradientClickeddb1()));
            wl->addWidget(m_labelGradientdb1);

            m_labelGradientdb2 = new GradientComboBox();
            m_labelGradientdb2->SetCurrentGradient(m_Style->m_ColorGradientb2);
            connect(m_labelGradientdb2,SIGNAL(OnGradientChanged()),this,SLOT(OnGradientClickeddb2()));
            wl->addWidget(m_labelGradientdb2);


            {
                wl->addWidget(new QLabel("First Parameter Band"));
                QSpinBox * m_BandBox = new QSpinBox();
                m_BandBox->setMaximum(1);
                m_BandBox->setMinimum(0);
                m_BandBox->setValue(m_Style->m_IndexB1);
                wl->addWidget(m_BandBox);

                QDoubleSpinBox * m_SpinMin;
                QDoubleSpinBox * m_SpinMax;

                m_SpinMax = new QDoubleSpinBox();
                m_SpinMax->setValue(m_Style->m_Intervalb1.GetMax());
                m_SpinMax->setDecimals(6);
                m_SpinMax->setMaximum(1e10);
                m_SpinMax->setMinimum(-1e10);

                m_SpinMin = new QDoubleSpinBox();
                m_SpinMin->setValue(m_Style->m_Intervalb1.GetMin());
                m_SpinMin->setDecimals(6);
                m_SpinMin->setMaximum(1e10);
                m_SpinMin->setMinimum(-1e10);


                QIcon *icon_re = new QIcon();
                icon_re->addFile((m_Dir + SPH_FOLDER_ASSETS + "refresh_24.png"), QSize(), QIcon::Normal, QIcon::Off);
                QToolButton * m_GetMinMaxButton;
                m_GetMinMaxButton = new QToolButton();
                m_GetMinMaxButton->setIcon(*icon_re);
                m_GetMinMaxButton->setIconSize(QSize(22,22));
                m_GetMinMaxButton->resize(22,22);

                wl->addWidget(new QLabeledWidget("Minimum Value",m_SpinMin));
                wl->addWidget(new QLabeledWidget("Maximum Value",m_SpinMax));
                wl->addWidget(new QLabeledWidget("Load Min and Max from Map",m_GetMinMaxButton));

                connect(m_GetMinMaxButton,SIGNAL(pressed()),this,SLOT(OnUpdateMinMax1()));
                connect(m_BandBox,SIGNAL(valueChanged(int)),this,SLOT(OnBandChanged1(int)));
                connect(m_SpinMin, SIGNAL(valueChanged(double)),this,SLOT(OnMinValueChanged1(double)));
                connect(m_SpinMax, SIGNAL(valueChanged(double)),this,SLOT(OnMaxValueChanged1(double)));
            }

            {
                wl->addWidget(new QLabel("Second Parameter Band Band"));
                QSpinBox * m_BandBox = new QSpinBox();
                m_BandBox->setMaximum(1);
                m_BandBox->setMinimum(0);
                m_BandBox->setValue(m_Style->m_IndexB2);
                wl->addWidget(m_BandBox);

                QDoubleSpinBox * m_SpinMin;
                QDoubleSpinBox * m_SpinMax;

                m_SpinMax = new QDoubleSpinBox();
                m_SpinMax->setValue(m_Style->m_Intervalb2.GetMax());
                m_SpinMax->setDecimals(6);
                m_SpinMax->setMaximum(1e10);
                m_SpinMax->setMinimum(-1e10);

                m_SpinMin = new QDoubleSpinBox();
                m_SpinMin->setValue(m_Style->m_Intervalb2.GetMin());
                m_SpinMin->setDecimals(6);
                m_SpinMin->setMaximum(1e10);
                m_SpinMin->setMinimum(-1e10);


                QIcon *icon_re = new QIcon();
                icon_re->addFile((m_Dir + SPH_FOLDER_ASSETS + "refresh_24.png"), QSize(), QIcon::Normal, QIcon::Off);
                QToolButton * m_GetMinMaxButton;
                m_GetMinMaxButton = new QToolButton();
                m_GetMinMaxButton->setIcon(*icon_re);
                m_GetMinMaxButton->setIconSize(QSize(22,22));
                m_GetMinMaxButton->resize(22,22);

                wl->addWidget(new QLabeledWidget("Minimum Value",m_SpinMin));
                wl->addWidget(new QLabeledWidget("Maximum Value",m_SpinMax));
                wl->addWidget(new QLabeledWidget("Load Min and Max from Map",m_GetMinMaxButton));

                connect(m_GetMinMaxButton,SIGNAL(pressed()),this,SLOT(OnUpdateMinMax2()));
                connect(m_BandBox,SIGNAL(valueChanged(int)),this,SLOT(OnBandChanged2(int)));
                connect(m_SpinMin, SIGNAL(valueChanged(double)),this,SLOT(OnMinValueChanged2(double)));
                connect(m_SpinMax, SIGNAL(valueChanged(double)),this,SLOT(OnMaxValueChanged2(double)));
            }

            QGroupBox * gbi = new QGroupBox();
            QVBoxLayout * gbil = new QVBoxLayout();
            gbi->setLayout(gbil);
            gbi->setTitle("Duo Band");
            gbil->addWidget(w);

            m_ToolBoxl->addWidget(gbi);
        }

        if(m_Style->m_HasTripleBand)
        {
            QWidget * w = new QWidget();
            QVBoxLayout * wl = new QVBoxLayout();
            w->setLayout(wl);
            wl->addItem(new QSpacerItem(20,600));

            {
                wl->addWidget(new QLabel("Red Display Band"));
                QSpinBox * m_BandBox = new QSpinBox();
                m_BandBox->setMaximum(m_Style->m_Bands-1);
                m_BandBox->setMinimum(0);
                m_BandBox->setValue(m_Style->m_IndexB1);
                wl->addWidget(m_BandBox);

                QDoubleSpinBox * m_SpinMin;
                QDoubleSpinBox * m_SpinMax;

                m_SpinMax = new QDoubleSpinBox();
                m_SpinMax->setValue(m_Style->m_Intervalb1.GetMax());
                m_SpinMax->setDecimals(6);
                m_SpinMax->setMaximum(1e10);
                m_SpinMax->setMinimum(-1e10);

                m_SpinMin = new QDoubleSpinBox();
                m_SpinMin->setValue(m_Style->m_Intervalb1.GetMin());
                m_SpinMin->setDecimals(6);
                m_SpinMin->setMaximum(1e10);
                m_SpinMin->setMinimum(-1e10);


                QIcon *icon_re = new QIcon();
                icon_re->addFile((m_Dir + SPH_FOLDER_ASSETS + "refresh_24.png"), QSize(), QIcon::Normal, QIcon::Off);
                QToolButton * m_GetMinMaxButton;
                m_GetMinMaxButton = new QToolButton();
                m_GetMinMaxButton->setIcon(*icon_re);
                m_GetMinMaxButton->setIconSize(QSize(22,22));
                m_GetMinMaxButton->resize(22,22);

                wl->addWidget(new QLabeledWidget("Minimum Value",m_SpinMin));
                wl->addWidget(new QLabeledWidget("Maximum Value",m_SpinMax));
                wl->addWidget(new QLabeledWidget("Load Min and Max from Map",m_GetMinMaxButton));

                connect(m_GetMinMaxButton,SIGNAL(pressed()),this,SLOT(OnUpdateMinMax1()));
                connect(m_BandBox,SIGNAL(valueChanged(int)),this,SLOT(OnBandChanged1(int)));
                connect(m_SpinMin, SIGNAL(valueChanged(double)),this,SLOT(OnMinValueChanged1(double)));
                connect(m_SpinMax, SIGNAL(valueChanged(double)),this,SLOT(OnMaxValueChanged1(double)));
            }

            {
                wl->addWidget(new QLabel("Green Display Band"));
                QSpinBox * m_BandBox = new QSpinBox();
                m_BandBox->setMaximum(m_Style->m_Bands-1);
                m_BandBox->setMinimum(0);
                m_BandBox->setValue(m_Style->m_IndexB2);
                wl->addWidget(m_BandBox);

                QDoubleSpinBox * m_SpinMin;
                QDoubleSpinBox * m_SpinMax;

                m_SpinMax = new QDoubleSpinBox();
                m_SpinMax->setValue(m_Style->m_Intervalb2.GetMax());
                m_SpinMax->setDecimals(6);
                m_SpinMax->setMaximum(1e10);
                m_SpinMax->setMinimum(-1e10);

                m_SpinMin = new QDoubleSpinBox();
                m_SpinMin->setValue(m_Style->m_Intervalb2.GetMin());
                m_SpinMin->setDecimals(6);
                m_SpinMin->setMaximum(1e10);
                m_SpinMin->setMinimum(-1e10);


                QIcon *icon_re = new QIcon();
                icon_re->addFile((m_Dir + SPH_FOLDER_ASSETS + "refresh_24.png"), QSize(), QIcon::Normal, QIcon::Off);
                QToolButton * m_GetMinMaxButton;
                m_GetMinMaxButton = new QToolButton();
                m_GetMinMaxButton->setIcon(*icon_re);
                m_GetMinMaxButton->setIconSize(QSize(22,22));
                m_GetMinMaxButton->resize(22,22);

                wl->addWidget(new QLabeledWidget("Minimum Value",m_SpinMin));
                wl->addWidget(new QLabeledWidget("Maximum Value",m_SpinMax));
                wl->addWidget(new QLabeledWidget("Load Min and Max from Map",m_GetMinMaxButton));

                connect(m_GetMinMaxButton,SIGNAL(pressed()),this,SLOT(OnUpdateMinMax2()));
                connect(m_BandBox,SIGNAL(valueChanged(int)),this,SLOT(OnBandChanged2(int)));
                connect(m_SpinMin, SIGNAL(valueChanged(double)),this,SLOT(OnMinValueChanged2(double)));
                connect(m_SpinMax, SIGNAL(valueChanged(double)),this,SLOT(OnMaxValueChanged2(double)));
            }


            {
                wl->addWidget(new QLabel("Blue Display Band"));
                QSpinBox * m_BandBox = new QSpinBox();
                m_BandBox->setMaximum(m_Style->m_Bands-1);
                m_BandBox->setMinimum(0);
                m_BandBox->setValue(m_Style->m_IndexB3);
                wl->addWidget(m_BandBox);

                QDoubleSpinBox * m_SpinMin;
                QDoubleSpinBox * m_SpinMax;

                m_SpinMax = new QDoubleSpinBox();
                m_SpinMax->setValue(m_Style->m_Intervalb3.GetMax());
                m_SpinMax->setDecimals(6);
                m_SpinMax->setMaximum(1e10);
                m_SpinMax->setMinimum(-1e10);

                m_SpinMin = new QDoubleSpinBox();
                m_SpinMin->setValue(m_Style->m_Intervalb3.GetMin());
                m_SpinMin->setDecimals(6);
                m_SpinMin->setMaximum(1e10);
                m_SpinMin->setMinimum(-1e10);


                QIcon *icon_re = new QIcon();
                icon_re->addFile((m_Dir + SPH_FOLDER_ASSETS + "refresh_24.png"), QSize(), QIcon::Normal, QIcon::Off);
                QToolButton * m_GetMinMaxButton;
                m_GetMinMaxButton = new QToolButton();
                m_GetMinMaxButton->setIcon(*icon_re);
                m_GetMinMaxButton->setIconSize(QSize(22,22));
                m_GetMinMaxButton->resize(22,22);

                wl->addWidget(new QLabeledWidget("Minimum Value",m_SpinMin));
                wl->addWidget(new QLabeledWidget("Maximum Value",m_SpinMax));
                wl->addWidget(new QLabeledWidget("Load Min and Max from Map",m_GetMinMaxButton));

                connect(m_GetMinMaxButton,SIGNAL(pressed()),this,SLOT(OnUpdateMinMax3()));
                connect(m_BandBox,SIGNAL(valueChanged(int)),this,SLOT(OnBandChanged3(int)));
                connect(m_SpinMin, SIGNAL(valueChanged(double)),this,SLOT(OnMinValueChanged3(double)));
                connect(m_SpinMax, SIGNAL(valueChanged(double)),this,SLOT(OnMaxValueChanged3(double)));
            }




            QGroupBox * gbi = new QGroupBox();
            QVBoxLayout * gbil = new QVBoxLayout();
            gbi->setLayout(gbil);
            gbi->setTitle("Multi Band");
            gbil->addWidget(w);

            m_ToolBoxl->addWidget(gbi);
        }
        if(m_Style->m_HasVectorPointLine)
        {
            QWidget * w = new LineStyleWidget(m_Layer,&(m_Style->m_PointLineStyle));

            QGroupBox * gbi = new QGroupBox();
            QVBoxLayout * gbil = new QVBoxLayout();
            gbi->setLayout(gbil);
            gbi->setTitle("Point Outline");
            gbil->addWidget(w);

            m_ToolBoxl->addWidget(gbi);
        }
        if(m_Style->m_HasVectorPointFill)
        {
            QWidget * w = new FillStyleWidget(m_Layer,&(m_Style->m_PointFillStyle));


            QGroupBox * gbi = new QGroupBox();
            QVBoxLayout * gbil = new QVBoxLayout();
            gbi->setLayout(gbil);
            gbi->setTitle("Point Fill");
            gbil->addWidget(w);

            m_ToolBoxl->addWidget(gbi);
        }
        if(m_Style->m_HasVectorLineLine)
        {
            QWidget * w = new LineStyleWidget(m_Layer,&(m_Style->m_LineLineStyle));

            QGroupBox * gbi = new QGroupBox();
            QVBoxLayout * gbil = new QVBoxLayout();
            gbi->setLayout(gbil);
            gbi->setTitle("Line");
            gbil->addWidget(w);

            m_ToolBoxl->addWidget(gbi);

        }
        if(m_Style->m_HasVectorPolygonLine)
        {
            QWidget * w  = new LineStyleWidget(m_Layer,&(m_Style->m_PolygonLineStyle));

            QGroupBox * gbi = new QGroupBox();
            QVBoxLayout * gbil = new QVBoxLayout();
            gbi->setLayout(gbil);
            gbi->setTitle("Polygon Outline");
            gbil->addWidget(w);

            m_ToolBoxl->addWidget(gbi);
        }
        if(m_Style->m_HasVectorPolygonFill)
        {
            QWidget * w = new FillStyleWidget(m_Layer,&(m_Style->m_PolygonFillStyle));

            QGroupBox * gbi = new QGroupBox();
            QVBoxLayout * gbil = new QVBoxLayout();
            gbi->setLayout(gbil);
            gbi->setTitle("Polygon Fill");
            gbil->addWidget(w);

            m_ToolBoxl->addWidget(gbi);
        }


    }

    inline void OnTimingChanged()
    {
        if(m_Timeslider != nullptr)
        {
            m_Timeslider->setValue(m_Style->m_CurrentTime);
        }
    }



public slots:


    //raster band gradients
    inline void OnGradientClickedsb1()
    {
        m_Style->m_ColorGradientb1 = m_labelGradientsb1->GetCurrentGradient();
    }

    inline void OnGradientClickeddb1()
    {
        m_Style->m_ColorGradientb1 = m_labelGradientdb1->GetCurrentGradient();
    }
    inline void OnGradientClickeddb2()
    {
        m_Style->m_ColorGradientb2 = m_labelGradientdb2->GetCurrentGradient();
    }


    //singleband settings

    inline void OnUpdateMinMax()
    {

    }
    inline void OnMaxValueChanged(double v)
    {
        m_Style->m_Intervalb1.SetMax(v);
    }
    inline void OnMinValueChanged(double v)
    {
        m_Style->m_Intervalb1.SetMin(v);
    }

    //multiband settings

    inline void OnUpdateMinMax1()
    {

    }

    inline void OnBandChanged1(int b)
    {
        m_Style->m_IndexB1 =b;
    }
    inline void OnMinValueChanged1(double v)
    {
        m_Style->m_Intervalb1.SetMin(v);
    }
    inline void OnMaxValueChanged1(double v)
    {
        m_Style->m_Intervalb1.SetMax(v);
    }



    inline void OnUpdateMinMax2()
    {

    }

    inline void OnBandChanged2(int b)
    {
        m_Style->m_IndexB2 =b;
    }
    inline void OnMinValueChanged2(double v)
    {
        m_Style->m_Intervalb2.SetMin(v);
    }
    inline void OnMaxValueChanged2(double v)
    {
        m_Style->m_Intervalb2.SetMax(v);
    }


    inline void OnUpdateMinMax3()
    {

    }

    inline void OnBandChanged3(int b)
    {
        m_Style->m_IndexB3 =b;
    }
    inline void OnMinValueChanged3(double v)
    {
        m_Style->m_Intervalb3.SetMin(v);
    }
    inline void OnMaxValueChanged3(double v)
    {
        m_Style->m_Intervalb3.SetMax(v);
    }


    //dem and hillshade stuff

    inline void OnVelocityClicked(bool state)
    {
        m_Style->m_IsVelocity = state;
    }

    inline void OnVelSpacingChanged(int val)
    {
        m_Style->m_VelSpacing = val;

    }

    inline void OnDemClicked(bool state)
    {
        m_Style->m_IsDEM = state;
    }

    inline void OnHSClicked(bool state)
    {
        m_Style->m_IsHS = state;
    }

    inline void OnDemScaleChanged(double scale)
    {

        m_Style->DemScale = scale;

    }

    inline void OnHSAngle1Changed(int val)
    {

        m_Style->angle_hor = val;

    }

    inline void OnHSAngle2Changed(int val)
    {
        m_Style->angle_vert = val;

    }

    //animation stuff
    inline void TimeChanged(int t)
    {
        m_Style->m_CurrentTime= t;
    }


    inline void OnAnimationStart()
    {
        m_Style->m_Play = true;

    }
    inline void OnAnimationPause()
    {
        m_Style->m_Play = false;

    }

    inline void OnAnimationStop()
    {
        m_Style->m_Play = false;
        m_Style->m_CurrentTime = m_Style->m_TimeMin;
    }

    inline void PlaySpeedChanged(double x)
    {
        m_Style->m_PlaySpeed = x;
    }

    inline void OnSurfaceClicked(bool x)
    {
        m_Style->m_IsSurface = x;
    }

    inline void OnSurfaceSecondClicked(bool x)
    {
        m_Style->m_UseSecondDuoBandAsHeight = x;
    }
    inline void OnSurfaceFlowClicked(bool x)
    {
        m_Style->m_IsSurfaceFlow = x;
    }
};




#endif // LAYERSTYLEWIDGET_H
