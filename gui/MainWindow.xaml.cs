using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Markup;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

using System.Runtime.InteropServices;

namespace TortinGUI
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {

        InputData inputData = new InputData();

        public MainWindow()
        {
            InitializeComponent();
        }

        [DllImport("TortinData.dll", CharSet = CharSet.Unicode, SetLastError = true)]
        private static extern int solve(InputData inputData);

        private void ResetButton_Click(object sender, RoutedEventArgs e)
        {
            ReactorTypeCombo.IsEnabled = false;

            AssemblyStack.Children.Clear();
            int number = Int32.Parse(AssemblyNumber.Text);
            for (int i = 0; i < number; i++)
            {
                GroupBox assembly = XamlReader.Parse(XamlWriter.Save(AssemblyPrototype)) as GroupBox;
                assembly.Visibility = Visibility.Visible;
                assembly.Header = "Assembly " + (i + 1);
                AssemblyStack.Children.Add(assembly);
                var grid = assembly.Content as Grid;
                SetVisibility(grid, Visibility.Collapsed);

                foreach (var c in grid.Children)
                {
                    if (c is CheckBox cb)
                    {
                        cb.Click += DefautBox_Click;
                    }
                }
            }
        }

        private void DefautBox_Click(object sender, RoutedEventArgs e)
        {
            CheckBox cb = (CheckBox)sender;
            Grid grid = (Grid)cb.Parent;
            Visibility visibility = cb.IsChecked == true ? Visibility.Collapsed : Visibility.Visible;

            SetVisibility(grid, visibility);
        }

        private void SetVisibility(Grid grid, Visibility visibility)
        {
            foreach (var c in grid.Children)
            {
                UIElement element = (UIElement)c;
                int row = Grid.GetRow(element);
                if (row > 1)
                {
                    element.Visibility = visibility;
                }
            }

            foreach (var c in grid.Children)
            {
                UIElement element = (UIElement)c;
                int row = Grid.GetRow(element);
                if (row > 1)
                {
                    if (visibility == Visibility.Visible && (element.Uid?.Length ?? 0) > 0)
                    {
                        foreach (var d in DefaultGrid.Children)
                        {
                            if (element.Uid == ((UIElement)d).Uid)
                            {
                                if (element is TextBox tb1 && d is TextBox tb2)
                                {
                                    tb1.Text = tb2.Text;
                                    foreach (var c2 in grid.Children)
                                    {
                                        UIElement element2 = (UIElement)c2;
                                        int row2 = Grid.GetRow(element2);
                                        if (row == row2)
                                        {
                                            element2.Visibility = tb2.Visibility;
                                        }
                                    }
                                }
                                if (element is ComboBox cx1 && d is ComboBox cx2)
                                {
                                    cx1.SelectedIndex = cx2.SelectedIndex;
                                }
                            }
                        }

                    }
                }
            }
        }

        private void NodePrototype_Loaded(object sender, RoutedEventArgs e)
        {
            NodePrototype.Visibility = Visibility.Collapsed;
        }

        private void ResetMapsButton_Click(object sender, RoutedEventArgs e)
        {
            GenerateNodes();

            GenerateMaps();
        }

        private void GenerateMaps()
        {

            int x = Int32.Parse(AssemblyX.Text) + Int32.Parse(ReflectorX.Text);
            int y = Int32.Parse(AssemblyY.Text) + Int32.Parse(ReflectorY.Text);
            int ax = Int32.Parse(AssemblyX.Text);
            int ay = Int32.Parse(AssemblyY.Text);

            AssemblyMap.Children.Clear();
            AssemblyMap.Width = 35 * x + 10;
            for (int i = 0; i < x*y; i++)
            {
                TextBox node = XamlReader.Parse(XamlWriter.Save(NodePrototype)) as TextBox;
                node.Visibility = Visibility.Visible;
                node.Text = String.Empty;
                AssemblyMap.Children.Add(node);
            }

            RotationMap.Children.Clear();
            RotationMap.Width = 35 * x + 10;
            for (int i = 0; i < x*y; i++)
            {
                TextBox node = XamlReader.Parse(XamlWriter.Save(NodePrototype)) as TextBox;
                node.Visibility = Visibility.Visible;
                node.Text = String.Empty;
                RotationMap.Children.Add(node);
            }

            BowingMapX.Children.Clear();
            BowingMapX.Width = 35 * ax + 10;
            for (int i = 0; i < ax * ay; i++)
            {
                TextBox node = XamlReader.Parse(XamlWriter.Save(NodePrototype)) as TextBox;
                node.Visibility = Visibility.Visible;
                node.Text = String.Empty;
                BowingMapX.Children.Add(node);
            }

            BowingMapY.Children.Clear();
            BowingMapY.Width = 35 * ax + 10;
            for (int i = 0; i < ax * ay; i++)
            {
                TextBox node = XamlReader.Parse(XamlWriter.Save(NodePrototype)) as TextBox;
                node.Visibility = Visibility.Visible;
                node.Text = String.Empty;
                BowingMapY.Children.Add(node);
            }

            ControlMap.Children.Clear();
            ControlMap.Width = 35 * ax + 10;
            for (int i = 0; i < ax * ay; i++)
            {
                TextBox node = XamlReader.Parse(XamlWriter.Save(NodePrototype)) as TextBox;
                node.Visibility = Visibility.Visible;
                node.Text = String.Empty;
                ControlMap.Children.Add(node);
            }

        }

        private void GenerateNodes()
        {
            NodeStack.Children.Clear();
            int count = NodeRelularCheckBox.IsChecked == true ? 1 : Int32.Parse(NodeCount.Text);
            for (int i = 0; i < count; i++)
            {
                TextBox node = XamlReader.Parse(XamlWriter.Save(NodePrototype)) as TextBox;
                node.Visibility = Visibility.Visible;
                node.Text = String.Empty;
                NodeStack.Children.Add(node);
            }
        }

        private void NodeRelularCheckBox_Click(object sender, RoutedEventArgs e)
        {
            GenerateNodes();
        }

        private void StartCalculationButton_Click(object sender, RoutedEventArgs e)
        {
            solve(inputData);
        }
    }

    public class ReactorConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
        {
            return (int)value > 0 ? Visibility.Collapsed : Visibility.Visible;
        }

        public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
        {
            throw new NotImplementedException();
        }
    }
}
